from __future__ import annotations
from datetime import datetime, timezone
from typing import Any

import pynmea2
import pytz
from timezonefinder import TimezoneFinder


timezone_finder = TimezoneFinder()


def find_first_valid_fix(parsed_lines: list[tuple[str, Any, Any]]):
    for (typechar, _, payload) in parsed_lines:
        if (typechar == 'g' and isinstance(payload, pynmea2.RMC)
                and payload.is_valid):
            return payload
    raise ValueError("no valid fix")


def infer_timezone_from_fix(rmc: pynmea2.RMC):
    return pytz.timezone(
        timezone_finder.timezone_at(lng=rmc.longitude, lat=rmc.latitude))


def utc_to_tz(utc: datetime, tz: timezone):
    return utc.replace(tzinfo=pytz.utc).astimezone(tz=tz)
