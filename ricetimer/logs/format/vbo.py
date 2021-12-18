from __future__ import annotations
from io import TextIOBase
from collections import defaultdict
from typing import Any, Optional

import pandas as pd
from pandas import DataFrame
import pynmea2
import pytz

from ricetimer.logs.utils import timezone_finder
from ricetimer.logs.utils import utc_to_tz


_HEADER_MID = """
[channel units]

[comments]

[column names]
"""

_VBO_COLUMNS = defaultdict(lambda: (None, None, ' {:f}'), {
    'num_sats': ('satellites', 'sats', ' {:03d}'),
    'lat': ('latitude', 'lat', ' {:+014.8f}'),
    'lon': ('longitude', 'long', ' {:+014.8f}'),
    'alt': ('height', 'height', ' {:+08.2f}'),
    'speed_kph': ('velocity kmh', 'velocity', ' {:07.3f}'),
    'course_deg': ('heading', 'heading', ' {:06.2f}'),
    'imu0': ('imu channel 0', 'imu0', ' {:+06.3f}'),
    'imu1': ('imu channel 1', 'imu1', ' {:+06.3f}'),
    'imu2': ('imu channel 2', 'imu2', ' {:+06.3f}'),
    'imu3': ('imu channel 3', 'imu3', ' {:+06.3f}'),
    'imu4': ('imu channel 4', 'imu4', ' {:+06.3f}'),
    'imu5': ('imu channel 5', 'imu5', ' {:+06.3f}'),
})


def write_vbo(table: DataFrame, f: TextIOBase):
    t0 = table.first_valid_index()
    try:
        tz = pytz.timezone(
            timezone_finder.timezone_at(
                lng=table.at[t0, 'lon'], lat=table.at[t0, 'lat']))
    except ValueError:
        tz = pytz.utc

    headers = ['time', *(_VBO_COLUMNS[col][1] or col
                         for col in table.columns)]
    formats = ['',  *(_VBO_COLUMNS[col][2]
                      for col in table.columns)]

    f.write(
        t0.to_pydatetime().strftime("File created on %d/%m/%y at %T\n"))
    f.write('[header]\n')
    f.write('time\n')
    for col_name in table.columns:
        f.write((_VBO_COLUMNS[col_name][0] or col_name) + '\n')
    f.write(_HEADER_MID)
    f.write(' '.join(headers) + '\n')
    f.write('\n\n[data]\n')
    for row in table.itertuples():
        for col_i, col in enumerate(row):
            if col_i == 0:
                f.write(utc_to_tz(col, tz).strftime('%H%M%S.%f')[:-3])
            else:
                if headers[col_i] == 'lat':
                    col *= 60
                elif headers[col_i] == 'long':
                    col *= -60
                try:
                    f.write(formats[col_i].format(col))
                except ValueError:
                    f.write(' ')
                    f.write(col)
        f.write('\n')
