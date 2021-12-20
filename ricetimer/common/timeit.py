import time

def timeit(method):
    def timed(*args, **kw):
        ts = time.perf_counter_ns()
        result = method(*args, **kw)
        te = time.perf_counter_ns()
        if 'log_time' in kw:
            name = kw.get('log_name', method.__name__.upper())
            kw['log_time'][name] = (te - ts) / 1e6
        else:
            print('%r  %.3f ms' % \
                  (method.__name__, (te - ts) / 1e6))
        return result
    return timed
