#pragma once

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Task {
 public:
  TaskHandle_t handle() const { return handle_; }
  virtual ~Task() = default;

 protected:
  TaskHandle_t handle_ = nullptr;

  explicit Task() {}

  virtual void Run() = 0;

  esp_err_t Spawn(const char* name, uint32_t stack_depth, uint32_t priority) {
    return xTaskCreate(RunAdapter, name, stack_depth, this, priority, &handle_) == pdTRUE
               ? ESP_OK
               : ESP_ERR_NO_MEM;
  }

  esp_err_t SpawnPinned(const char* name, uint32_t stack_depth, uint32_t priority, BaseType_t cpu) {
    return xTaskCreatePinnedToCore(RunAdapter, name, stack_depth, this, priority, &handle_, cpu) ==
                   pdTRUE
               ? ESP_OK
               : ESP_ERR_NO_MEM;
  }

  esp_err_t SpawnSame(const char* name, uint32_t stack_depth, uint32_t priority) {
    return SpawnPinned(name, stack_depth, priority, xPortGetCoreID());
  }

  void Kill() {
    if (handle_) {
      vTaskDelete(handle_);
      handle_ = nullptr;
    }
  }

 private:
  Task(const Task&) = delete;
  Task(Task&&) = delete;
  Task& operator=(const Task&) = delete;
  static void RunAdapter(void* self) { reinterpret_cast<Task*>(self)->Run(); }
};
