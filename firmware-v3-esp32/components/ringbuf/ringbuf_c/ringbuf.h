/*
 * Copyright (c) 2016 Mindaugas Rasiukevicius <rmind at noxt eu>
 * All rights reserved.
 *
 * Use is subject to license terms, as specified in the LICENSE file.
 */

#ifndef _RINGBUF_H_
#define _RINGBUF_H_

#if __has_include("esp_attr.h")
#include "esp_attr.h"
#endif  // __has_include("esp_attr.h")

#ifndef IRAM_ATTR
#define IRAM_ATTR
#endif  // IRAM_ATTR

__BEGIN_DECLS

typedef struct ringbuf ringbuf_t;
typedef struct ringbuf_worker ringbuf_worker_t;

int ringbuf_setup(ringbuf_t*, unsigned, size_t);
void ringbuf_get_sizes(unsigned, size_t*, size_t*);

ringbuf_worker_t* ringbuf_register(ringbuf_t*, unsigned);
void ringbuf_unregister(ringbuf_t*, ringbuf_worker_t*);

IRAM_ATTR ssize_t ringbuf_acquire(ringbuf_t*, ringbuf_worker_t*, size_t);
IRAM_ATTR ssize_t ringbuf_acquire_i(ringbuf_t*, int, size_t);
IRAM_ATTR void ringbuf_produce(ringbuf_t*, ringbuf_worker_t*);
IRAM_ATTR void ringbuf_produce_i(ringbuf_t*, int);
IRAM_ATTR size_t ringbuf_consume(ringbuf_t*, size_t*);
IRAM_ATTR void ringbuf_release(ringbuf_t*, size_t);

__END_DECLS

#endif
