from __future__ import annotations
from datetime import datetime
import logging
from pathlib import Path
from typing import Any, Literal, Optional

import cantools.database
from cantools.database import Database
import numpy as np
import pandas as pd
from pandas import DataFrame, Series
import pynmea2
import scipy.interpolate

from ricetimer import DATA_PATH
from ricetimer.logs.extract import extract_gnss_signals
from ricetimer.logs.extract import extract_raw_imu_signals
from ricetimer.logs.extract import extract_can_signals


DBC_PATH = DATA_PATH / 'dbc'


def tabulate_with_profile(events: list[tuple[str, float, Any]], profile):
    gnss_signals = extract_gnss_signals(events)
    raw_imu_signals = extract_raw_imu_signals(events)

    if profile:
        can_db, can_signals_spec, can_interp_methods = can_spec_from_profile(
            profile)
        can_signals = extract_can_signals(can_db, can_signals_spec, events)
    else:
        can_db = None
        can_signals = []
        can_interp_methods = []

    return pd.concat([
        gnss_signals,
        resample_signal(gnss_signals.index, raw_imu_signals, 'linear'),
        *(resample_signal(gnss_signals.index, DataFrame(can_signal), can_interp_methods[i])
          for i, can_signal in enumerate(can_signals) if can_signal is not None),
    ], axis = 1)


def can_spec_from_profile(profile: dict):
    can_db_path_rel=Path(profile['can']['db'])
    if can_db_path_rel.is_absolute():
        can_db_path=can_db_path_rel
    else:
        can_db_path=DBC_PATH / can_db_path_rel
    can_db: Database=cantools.database.load_file(can_db_path)

    can_signals_spec: list[tuple[str, str]]=[]
    can_interp_methods: list[str]=[]
    for key, spec in profile['can']['signals'].items():
        can_message_name, can_signal_name=key.split('.', maxsplit = 1)
        if isinstance(spec, str):
            column_name=spec
            interp_method='previous'
        elif isinstance(spec, dict):
            column_name=spec['name']
            interp_method=spec['interp']
        else:
            logging.warning(
                f'invalid can signal specification: {key} = {spec}')
            continue
        can_signals_spec.append(
            (can_message_name, can_signal_name, column_name))
        can_interp_methods.append(interp_method)

    return (can_db, can_signals_spec, can_interp_methods)


_SIMPLE_METHOD_DICT = {
    'previous': 'ffill',
    'next': 'bfill',
    'nearest': 'nearest',
}


def resample_signal(new_timestamps: Series, signal: DataFrame, interp_method: str):
    # try to use pandas native reindex method to perform trivial resampling
    if interp_method in _SIMPLE_METHOD_DICT:
        reindexed = signal.reindex(new_timestamps,
                                   method=_SIMPLE_METHOD_DICT[interp_method])
        reindexed.fillna(method='bfill', inplace=True)
        reindexed.fillna(method='ffill', inplace=True)
        return reindexed

    # otherwise use scipy interpolation
    new_timestamps_np = new_timestamps.to_numpy().astype(np.float64)
    old_timestamps_np = signal.index.to_numpy().astype(np.float64)
    resampled_signal = DataFrame(
        index=new_timestamps, columns=signal.columns)
    for dim_i in range(len(signal.columns)):
        interpolator = scipy.interpolate.interp1d(
            x=old_timestamps_np,
            y=signal.iloc[:, dim_i],
            kind=interp_method,
            copy=False,
            fill_value='extrapolate',
            # assume_sorted=True,
        )
        resampled_signal.iloc[:, dim_i] = interpolator(new_timestamps_np)
    return resampled_signal
