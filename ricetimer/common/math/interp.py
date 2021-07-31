import numba
import numpy as np


# reference: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0811r3.html
@numba.njit
def lerp(a: float, b: float, t: float) -> float:
    """Return a + t * (b - a) in a numerically stable way."""
    if (a <= 0 and b >= 0) or (a >= 0 and b <= 0):
        return t*b + (1 - t)*a
    if t == 1:
        return b
    x = a + t * (b - a)
    return max(b, x) if t > 1 == b > a else min(b, x)


@numba.njit
def interp_rolling_uint32(x: float, xs: np.ndarray, ys: np.ndarray, extrapolate: bool = True) -> float:
    n = len(xs)
    gaps = np.diff(xs.astype(np.uint32))
    deltas = (x - xs).astype(np.int32)
    for i in range(n):
        if deltas[i] <= 0:
            break
    else:
        return ys[-1] if extrapolate else np.nan
    if i == 0:
        return ys[0] if extrapolate else np.nan
    ratio = deltas[i - 1] / gaps[i - 1]
    return lerp(ys[i - 1], ys[i], ratio)
