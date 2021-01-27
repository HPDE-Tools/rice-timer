#pragma once

#include "esp_err.h"
#include "esp_log.h"

#define OK_OR_RETURN(x, ret)                                                                  \
  do {                                                                                        \
    if (const esp_err_t err = (x); err != ESP_OK) {                                           \
      ESP_LOGE("", "%s:%d TRY(" #x ") fail => %s", __FILE__, __LINE__, esp_err_to_name(err)); \
      return ret;                                                                             \
    }                                                                                         \
  } while (0)

#define TRY(x) OK_OR_RETURN(x, err)

#define CHECK(x)                                                    \
  do {                                                              \
    if (!(x)) {                                                     \
      ESP_LOGE("", "%s:%d CHECK(" #x ") fail", __FILE__, __LINE__); \
      while (1) {                                                   \
      }                                                             \
    }                                                               \
  } while (0)

#define CHECK_OK(x)                                                                              \
  do {                                                                                           \
    const esp_err_t result = (x);                                                                \
    if (result != ESP_OK) {                                                                      \
      ESP_LOGE(                                                                                  \
          "", "%s:%d CHECK_OK(" #x ") fail => %s", __FILE__, __LINE__, esp_err_to_name(result)); \
      while (1) {                                                                                \
      }                                                                                          \
    }                                                                                            \
  } while (0)
