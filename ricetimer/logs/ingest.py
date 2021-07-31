from __future__ import annotations
from datetime import datetime
from itertools import chain
import logging
from typing import Any, Optional, Iterable

import numba
import numpy as np
import pynmea2

from ricetimer.common.math import interp_rolling_uint32

"""
Functions for converting raw log lines into structured events with high-resolution timestamps.
"""


def ingest_log_lines(lines: Iterable[str], *, window_half_width: int = 2):
    """
    Parse all lines from the raw log and perform timestamp recovery.
    Return a list of valid timestamped events, each consisting of the following parts:

    - type character (see below)
    - high-resolution UNIX timestamp (UTC time)
    - type-specific parsed data:
        - 'g' (GNSS): parsed NMEA sentence
        - 'i' (IMU raw): list of float
        - 'c' (CAN raw): (id, len, data)
    """
    parsed_lines = [
        parsed for line in lines
        if (parsed := parse_line(line)) is not None]
    return recover_timestamps(parsed_lines, window_half_width=window_half_width)


def parse_line(line: str):
    """
    Parse a line in the raw log into the following parts:
    - type character
    - rolling timestamp value (uint32)
    - type-specific parsed data

    If a line cannot be parsed, return None.
    """
    try:
        typechar, capture_str, payload = line.split(',', maxsplit=2)
        capture = int(capture_str)
    except ValueError:
        logging.warning(f'malformed log line: {repr(line)}')
        return None

    if typechar == 'g':
        # GNSS reading
        # payload: raw NMEA sentence from '$' to checksum (inclusive)
        parsed = _parse_nmea(payload)
    elif typechar == 'p':
        # PPS event matched to a GNSS reading
        # payload: unix time (UTC) in whole seconds at PPS event
        parsed = _parse_pps(payload)
    elif typechar == 'i':
        # Raw IMU data
        # payload: comma-separated (arbitrary) numbers
        parsed = _parse_raw_imu(payload)
    elif typechar == 'c':
        # CAN frame
        # payload: text serialization of the CAN frame
        #   e.g. "b0b1b2b3,8,d0d1d2d3d4d5d6d7"
        parsed = _parse_can(payload)
    else:
        logging.warning(f'unrecognized type character: {typechar}')
        return None

    if parsed is None:
        return None
    return typechar, capture, parsed


def _parse_nmea(nmea: str) -> Optional[pynmea2.NMEASentence]:
    try:
        return pynmea2.parse(nmea, check=True)
    except ValueError as e:
        logging.warning(f'cannot parse NMEA {repr(nmea)}: {e}')
        return None


def _parse_pps(unix_str: str):
    try:
        return int(unix_str)
    except ValueError:
        logging.warning(f'PPS timestamp invalid: {repr(unix_str)}')
        return None


def _parse_raw_imu(raw_imu_str: str):
    try:
        return list(map(float, raw_imu_str.split(',')))
    except ValueError:
        logging.warning(f'raw IMU data invalid: {repr(raw_imu_str)}')
        return None


def _parse_can(can_frame_str: str):
    try:
        id_str, dlc_str, data_str = can_frame_str.split(',', maxsplit=3)
        id = int(id_str, base=16)
        dlc = int(dlc_str)
        data = bytes.fromhex(data_str)
        if not (0 <= dlc <= 8 and len(data) == dlc):
            return None
        return (id, dlc, data)
    except ValueError:
        logging.warning(f'invalid CAN frame: {repr(can_frame_str)}')
        return None


def recover_timestamps(parsed_lines: list[tuple[str, int, Any]],
                       window_half_width=2):
    """
    Convert 32-bit rolling timestamps in the parsed logs to GNSS time by interpolating nearby PPS events.
    This only requires the PPS events to be ordered by the time they happened.
    All other log lines may be locally out-of-order and still be assigned the correct timestamp.

    In the result:
    - PPS events are be discarded as they only provide timing information.
    - Lines not between two PPS events, or severely out of order, are discarded.
    """
    pps_events = _filter_pps_from_parsed(parsed_lines)
    typechars, captures = _typechar_capture_from_parsed(parsed_lines)
    timestamps = _interp_timestamps(typechars,
                                    captures,
                                    pps_events,
                                    window_half_width=window_half_width)
    return [(typechar, datetime.utcfromtimestamp(timestamp), payload)
            for i, (typechar, _, payload) in enumerate(parsed_lines)
            if np.isfinite(timestamp := timestamps[i])]


def _filter_pps_from_parsed(
        parsed_lines: list[tuple[str, int, Any]]) -> np.ndarray:
    pps_events = np.fromiter(chain.from_iterable(
        (i, capture, timestamp)
        for i, (typechar, capture, timestamp) in enumerate(parsed_lines)
        if typechar == 'p'),
        dtype=np.int64).reshape((-1, 3))

    # make sure PPS unix timestamps are at least strictly sorted
    if not np.all(np.diff(pps_events[:, 2]) > 0):
        raise ValueError('PPS events out of order in input')

    return pps_events


def _typechar_capture_from_parsed(parsed_lines: list[tuple[str, int, Any]]):
    return (np.array([x for x, _, _ in parsed_lines]), np.array([y for _, y, _ in parsed_lines]))


@numba.njit
def _interp_timestamps(typechars,
                       captures,
                       pps_events: np.ndarray,
                       window_half_width: int):
    # TODO(summivox): more robust algorithm that takes care of long stretches of missing PPS
    # For now, make sure the window is "reasonably sized", defined as spanning not across 32-bit
    # counter overflow at the default clock rate of 80 MHz.
    ROLLOVER_LIMIT_SEC = 2**32 / 80e6 / 4

    n = len(typechars)
    timestamps = np.zeros(n, dtype=np.double)
    last_seen_pps_index = -1
    window = pps_events[0:window_half_width + 1, :]
    for i in range(n):
        # update PPS interpolation window
        if typechars[i] == 'p':
            last_seen_pps_index = min(last_seen_pps_index + 1,
                                      len(pps_events) - 1)
            window_low = max(last_seen_pps_index - window_half_width, 0)
            window_high = min(last_seen_pps_index + window_half_width + 1,
                              len(pps_events))
            window = pps_events[window_low:window_high, :]
            # check window time span not too large to cause 32-bit counter overflow`
            if window[-1, 2] - window[0, 2] > ROLLOVER_LIMIT_SEC:
                raise ValueError('gap too large')
            timestamps[i] = np.nan
            continue

        # discard any line not within the PPS window in the lines
        if not window[0, 0] <= i <= window[-1, 0]:
            timestamps[i] = np.nan
            continue

        # interpolate from rolling timestamp to unix timestamp
        timestamps[i] = interp_rolling_uint32(
            captures[i], window[:, 1], window[:, 2], extrapolate=False)
    return timestamps
