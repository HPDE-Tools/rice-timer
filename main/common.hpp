#pragma once

#include "esp_log.h"

#include "scope_guard.hpp"

#define TRY(x)                                                                                   \
  do {                                                                                           \
    const esp_err_t result = (x);                                                                \
    if (result != ESP_OK) {                                                                      \
      ESP_LOGE("", "%s:%d TRY(" #x ") fail => %s", __FILE__, __LINE__, esp_err_to_name(result)); \
      return result;                                                                             \
    }                                                                                            \
  } while (0)

#define CHECK(x)                                                    \
  do {                                                              \
    const bool result = (x);                                        \
    if (!result) {                                                  \
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


// TODO(summivox): experiment with I2C transaction-level mutex
void InitI2cMutex();
void TakeI2cMutex();
void ReleaseI2cMutex();
