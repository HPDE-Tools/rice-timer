from __future__ import annotations
from datetime import datetime
from itertools import chain
import logging
from typing import Any, Optional, Iterable

import numpy as np
import pynmea2
from scipy.interpolate import interp1d

from ricetimer.common.timeit import timeit
from ricetimer.common.math import interp_rolling_uint32, unwrap_uint32

"""
Functions for converting raw log lines into structured events with high-resolution timestamps.
"""


def ingest_log_lines(lines: Iterable[str], use_pps=True):
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
    parsed_lines = parse_lines(lines)
    # TODO(summivox): configurable gap threshold
    heartbeat_filtered_lines = exclude_heartbeat_gaps(parsed_lines, 8000)
    return recover_timestamps(heartbeat_filtered_lines, use_pps=use_pps)


def parse_lines(lines: Iterable[str]):
    """
    Parse all lines from the raw log.
    Return a list of valid events, each consisting of the following parts:

    - type character (see below)
    - raw 32-bit rolling timestamp
    - type-specific parsed data:
        - 'g' (GNSS): parsed NMEA sentence
        - 'i' (IMU raw): list of float
        - 'c' (CAN raw): (id, len, data)
    """
    return [
        parsed for line in lines
        if (parsed := parse_line(line)) is not None]


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
    elif typechar == 'h':
        # Heartbeat
        # payload: time elapsed in OS ticks (milliseconds) since device boot as uint32
        parsed = _parse_heartbeat(payload)
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


def _parse_heartbeat(uptime_str: str):
    # NOTE(summivox): This is the same as `_parse_pps` except for semantics.
    try:
        return int(uptime_str)
    except ValueError:
        logging.warning(f'Heartbeat invalid: {repr(uptime_str)}')
        return None


def exclude_heartbeat_gaps(parsed_lines: list[tuple[str, int, Any]], threshold_ms: int):
    """
    When we encounter large gaps between consecutive heartbeats, every event between them should be excluded from processing.
    """
    heartbeats = _filter_heartbeat_from_parsed(parsed_lines)  # (i, capture, uptime)
    if heartbeats.shape[0] < 2:
        return parsed_lines
    uptime_diffs = np.diff(heartbeats[:, 2].astype(np.uint32)).astype(np.int32)
    uptime_gap_indices = np.argwhere(uptime_diffs > threshold_ms)
    excluded = np.zeros(len(parsed_lines), dtype=np.bool8)
    for gap_index in uptime_gap_indices:
        excluded[heartbeats[gap_index, 0]:heartbeats[gap_index + 1, 0]] = 1
    return [line for i, line in enumerate(parsed_lines) if not excluded[i]]


def recover_timestamps(parsed_lines: list[tuple[str, int, Any]],
                       use_pps=True) -> list[tuple[str, float, Any]]:
    """
    Convert 32-bit rolling timestamps in the parsed log lines to either:

    - `use_pps == True`: GNSS timestamp (s) since the UNIX epoch, as interpolated / extrapolated from PPS
      events (capture clock + GNSS timestamp).
      This only requires the PPS events ('p') to be strictly monotonic.
      All other log lines may be locally out-of-order and still be assigned the correct timestamp.

    - `use_pps == False`: Estimated time elapsed (s) since the first event, as measured by the capture clock.

    Regardless, PPS events are excluded from the result as they do not provide information other than timing,
    which is already encoded into the result.
    """
    captures = _captures_from_parsed(parsed_lines)
    captures_unwrapped = unwrap_uint32(captures)
    captures_unwrapped -= captures_unwrapped[0]

    if use_pps:
        pps_events = _filter_pps_from_parsed(
            parsed_lines, captures_unwrapped)  # (i, capture, utctime)
        timestamps = _interp_timestamps(captures_unwrapped, pps_events)
        return [(typechar, timestamp, payload)
                for i, (typechar, _, payload) in enumerate(parsed_lines)
                if np.isfinite(timestamp := timestamps[i])]
    else:
        # TODO: unify the relative / absolute pipelines
        return [(typechar, captures_unwrapped[i] / 80e6, payload)
                for i, (typechar, _, payload) in enumerate(parsed_lines)
                if typechar not in ['p', 'h']]


def _captures_from_parsed(parsed_lines: list[tuple[str, int, Any]]):
    captures = np.empty(len(parsed_lines), dtype=np.uint32)
    for i, (_, capture, _) in enumerate(parsed_lines):
        captures[i] = capture
    return captures


def _filter_pps_from_parsed(
        parsed_lines: list[tuple[str, int, Any]],
        captures_unwrapped: np.ndarray) -> np.ndarray:
    pps_events = np.array([
        (i, captures_unwrapped[i], timestamp)
        for i, (typechar, _, timestamp) in enumerate(parsed_lines)
        if typechar == 'p'
    ])

    # validate that PPS captures are monotonically increasing
    if not np.all(np.diff(pps_events[:, 1]) > 0):
        raise ValueError('PPS events captures out of order in input')

    # validate that PPS unix timestamps are monotonically increasing
    if not np.all(np.diff(pps_events[:, 2]) > 0):
        raise ValueError('PPS events timestamps out of order in input')

    return pps_events


def _filter_heartbeat_from_parsed(
        parsed_lines: list[tuple[str, int, Any]]) -> np.ndarray:
    heartbeat_events = np.array([
        (i, capture, uptime)
        for i, (typechar, capture, uptime) in enumerate(parsed_lines)
        if typechar == 'h'
    ])
    return heartbeat_events


def _interp_timestamps(captures_unwrapped: np.ndarray,
                       pps_events: np.ndarray):
    timestamps = interp1d(
        pps_events[:, 1], pps_events[:, 2], fill_value='extrapolate')(captures_unwrapped)
    for i, _, _ in pps_events:
        timestamps[i] = np.nan
    return timestamps
