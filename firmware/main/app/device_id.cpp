// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/device_id.hpp"

#include "esp_system.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "scope_guard/scope_guard.hpp"

#include "common/macros.hpp"

namespace app {

namespace {

constexpr char TAG[] = "id";

}  // namespace

// statically initialize using IIFE
const std::array<uint8_t, 6> g_device_mac{[]() {
  std::array<uint8_t, 6> ret;
  esp_efuse_mac_get_default(ret.data());
  return ret;
}()};

void LogDeviceMac() {
  ESP_LOGI(
      TAG,
      "device mac: %02X:%02X:%02X:%02X:%02X:%02X",
      g_device_mac[0],
      g_device_mac[1],
      g_device_mac[2],
      g_device_mac[3],
      g_device_mac[4],
      g_device_mac[5]);
}

esp_err_t NvsInit() {
  static bool done = false;
  if (done) {
    return ESP_OK;
  }
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    // NVS partition was truncated and needs to be erased
    // Retry nvs_flash_init
    TRY(nvs_flash_erase());
    err = nvs_flash_init();
  }
  if (err == ESP_OK) {
    done = true;
  }
  return err;
}

int64_t NewSessionId() {
  static constexpr char kNamespace[] = "storage";
  static constexpr char kSessionIdKey[] = "session_id";

  OK_OR_RETURN(NvsInit(), -1);
  nvs_handle_t nvs;
  OK_OR_RETURN(nvs_open(kNamespace, NVS_READWRITE, &nvs), -1);
  SCOPE_EXIT { nvs_close(nvs); };

  int64_t session_id = -1;
  if (const esp_err_t err = nvs_get_i64(nvs, kSessionIdKey, &session_id);
      err == ESP_ERR_NVS_NOT_FOUND) {
    session_id = 0;
  } else if (err == ESP_OK) {
    ++session_id;
  } else {
    return err;
  }
  OK_OR_RETURN(nvs_set_i64(nvs, kSessionIdKey, session_id), -1);
  OK_OR_RETURN(nvs_commit(nvs), -1);
  return session_id;
}

};  // namespace app
