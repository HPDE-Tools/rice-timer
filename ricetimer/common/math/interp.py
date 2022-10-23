import numpy as np
import logging


# reference: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0811r3.html
def lerp(a: float, b: float, t: float) -> float:
    """Return a + t * (b - a) in a numerically stable way."""
    if (a <= 0 and b >= 0) or (a >= 0 and b <= 0):
        return t*b + (1 - t)*a
    if t == 1:
        return b
    x = a + t * (b - a)
    return max(b, x) if t > 1 == b > a else min(b, x)


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


def unwrap_uint32(xs: np.ndarray, out_dtype=np.int64) -> np.ndarray:
    """
    Similar to "unwrap" function from GNU Octave [1], only with modulo = 2**32 instead of 2*pi.

    [1]: https://octave.sourceforge.io/octave/function/unwrap.html
    """
    # TODO(summivox): define the threshold?
    diffs = np.diff(xs.astype(np.uint32), prepend=0).astype(np.int32)
    large_diff_indices = np.argwhere(np.abs(diffs) > 4e8)
    if len(large_diff_indices) > 0:
        i = large_diff_indices[0]
        logging.warning(f"Found unusual capture timestamp jump at line {i}: diff = {diffs[i]}.")
    return diffs.astype(out_dtype).cumsum()
