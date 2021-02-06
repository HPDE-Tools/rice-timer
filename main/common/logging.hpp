// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "esp_err.h"
#include "esp_log.h"

#if CONFIG_ESP_SYSTEM_PANIC_PRINT_HALT
#define DIEDIEDIE abort()
#else
#warning "Consider changing system panic behavior to CONFIG_ESP_SYSTEM_PANIC_PRINT_HALT."
#define DIEDIEDIE while (1)
#endif

#define OK_OR_RETURN(x, ret)                                                                  \
  do {                                                                                        \
    if (const esp_err_t err = (x); err != ESP_OK) {                                           \
      ESP_LOGE("", "%s:%d TRY(%s) fail => %s", __FILE__, __LINE__, #x, esp_err_to_name(err)); \
      return ret;                                                                             \
    }                                                                                         \
  } while (0)

#define TRY(x) OK_OR_RETURN(x, err)

#define CHECK(x)                                                    \
  do {                                                              \
    if (!(x)) {                                                     \
      ESP_LOGE("", "%s:%d CHECK(%s) fail", __FILE__, __LINE__, #x); \
      DIEDIEDIE;                                                    \
    }                                                               \
  } while (0)

#define CHECK_OK(x)                                                                              \
  do {                                                                                           \
    const esp_err_t result = (x);                                                                \
    if (result != ESP_OK) {                                                                      \
      ESP_LOGE(                                                                                  \
          "", "%s:%d CHECK_OK(%s) fail => %s", __FILE__, __LINE__, #x, esp_err_to_name(result)); \
      DIEDIEDIE;                                                                                 \
    }                                                                                            \
  } while (0)

#define CHECK_NOTNULL(x)                                                    \
  ({                                                                        \
    auto&& xx = (x);                                                        \
    if (xx == nullptr) {                                                    \
      ESP_LOGE("", "%s:%d CHECK_NOTNULL(%s) fail", __FILE__, __LINE__, #x); \
      DIEDIEDIE;                                                            \
    }                                                                       \
    xx;                                                                     \
  })
