from __future__ import annotations
from dataclasses import dataclass, astuple
from datetime import datetime
import logging
from typing import Any

from cantools.database import Database, Message
import numpy as np
from pandas import DataFrame, Series
import pynmea2


KPH_IN_KNOT = 1.852


@dataclass
class GnssSignal:
    timestamp: datetime = datetime.now()
    lat: float = 0
    lon: float = 0
    alt: float = 0
    speed_kph: float = 0
    course_deg: float = 0
    num_sats: float = 0


def extract_gnss_signals(events: list[tuple[str, float, Any]]):
    # NOTE: GNSS sentences of different types that are transmitted together represent
    # a single data point at a single instant. Each group is led by its RMC sentence.
    signal_data = []
    last_signal = GnssSignal()
    rmc = None
    gga = None

    def commit():
        nonlocal last_signal
        nonlocal rmc
        nonlocal gga
        if rmc is None:
            return
        signal = GnssSignal(last_signal)
        signal.timestamp = rmc.datetime
        signal.lat = rmc.latitude
        signal.lon = rmc.longitude
        signal.speed_kph = (rmc.spd_over_grnd or 0.0) * KPH_IN_KNOT
        signal.course_deg = rmc.true_course or signal.course_deg or 0.0
        if gga:
            try:
                signal.alt = gga.altitude
                signal.num_sats = int(gga.num_sats)
            except ValueError:
                pass
            if rmc.timestamp != gga.timestamp:
                logging.warning(
                    f'mismatch rmc/gga times: {rmc.timestamp} vs {gga.timestamp}')

        signal_data.append(astuple(signal))
        last_signal = signal
        rmc = None
        gga = None

    for typechar, _, payload in events:
        if typechar != 'g':
            continue
        if isinstance(payload, pynmea2.RMC):
            commit()
            rmc = payload
        if isinstance(payload, pynmea2.GGA):
            gga = payload
    commit()

    if not signal_data:
        return None
    return DataFrame.from_records(
        signal_data,
        columns=('timestamp', 'lat', 'lon', 'alt',
                 'speed_kph', 'course_deg', 'num_sats',),
        index='timestamp')


def extract_raw_imu_signals(events: list[tuple[str, float, Any]]):
    raw_imu_events = [
        (datetime.utcfromtimestamp(timestamp), *payload)
        for typechar, timestamp, payload in events if typechar == 'i'
    ]
    if not raw_imu_events:
        return None
    dims = len(raw_imu_events[0]) - 1
    column_names = [f'imu{i}' for i in range(dims)]
    return DataFrame.from_records(
        raw_imu_events,
        columns=('timestamp', *column_names),
        index='timestamp')


def extract_can_signals(can_db: Database,
                        signals_spec: list[tuple[str, str, str]],
                        events: list[tuple[str, float, Any]]):
    num_signals = len(signals_spec)
    if num_signals == 0:
        return []
    decode_dict = _build_can_decode_dict(can_db, signals_spec)
    signals_data: list[tuple[datetime, float]] = [[] for _ in range(num_signals)]
    fail_to_decode_ids = set()
    for typechar, timestamp, payload in events:
        if typechar != 'c':
            continue
        can_id, dlc, data = payload
        try:
            msg, signal_dict = decode_dict[can_id]
        except KeyError:
            continue
        try:
            signals = msg.decode(data, decode_choices=False)  # TODO: make this an option
        except ValueError as e:
            if can_id not in fail_to_decode_ids:
                logging.warning(
                    f'cannot decode: id=0x{can_id:08X} dlc={dlc} data={data.hex()} => {e}')
                fail_to_decode_ids.add(can_id)
            continue
        for sig_name, sig_value in signals.items():
            try:
                signals_data[signal_dict[sig_name]].append(
                    (datetime.utcfromtimestamp(timestamp), sig_value))
            except KeyError:
                continue

    result: list[Series | None] = [None] * num_signals
    for i, signal_data in enumerate(signals_data):
        if not signal_data:
            continue
        signal_array = np.array(signal_data)
        result[i] = Series(signal_array[:, 1],
                           index=signal_array[:, 0],
                           name=signals_spec[i][2])
    return result


def _build_can_decode_dict(can_db: Database, signals_spec: list[tuple[str, str, str]]):
    """CAN ID => (message decoder object, signal name => signal index)"""
    decode_dict: dict[int, tuple[Message, dict[str, int]]] = dict()
    for i, (msg_name, sig_name, _) in enumerate(signals_spec):
        try:
            msg = can_db.get_message_by_name(msg_name)
        except KeyError:
            continue
        decode_dict.setdefault(msg.frame_id, (msg, dict()))[1][sig_name] = i
    return decode_dict
