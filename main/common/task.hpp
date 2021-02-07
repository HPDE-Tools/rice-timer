// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <atomic>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Task {
 public:
  TaskHandle_t handle() const { return handle_.load(); }
  virtual ~Task() { Kill(); }

 protected:
  static_assert(std::atomic<TaskHandle_t>::is_always_lock_free);

  explicit Task() {}

  virtual void Run() = 0;

  esp_err_t Spawn(const char* name, uint32_t stack_depth, uint32_t priority) {
    Kill();
    TaskHandle_t handle = nullptr;
    if (xTaskCreate(RunAdapter, name, stack_depth, this, priority, &handle) != pdTRUE) {
      return ESP_ERR_NO_MEM;
    }
    handle_.store(handle);
    return ESP_OK;
  }

  esp_err_t SpawnPinned(const char* name, uint32_t stack_depth, uint32_t priority, BaseType_t cpu) {
    Kill();
    TaskHandle_t handle = nullptr;
    if (xTaskCreatePinnedToCore(RunAdapter, name, stack_depth, this, priority, &handle, cpu) !=
        pdTRUE) {
      return ESP_ERR_NO_MEM;
    }
    handle_.store(handle);
    return ESP_OK;
  }

  esp_err_t SpawnSame(const char* name, uint32_t stack_depth, uint32_t priority) {
    return SpawnPinned(name, stack_depth, priority, xPortGetCoreID());
  }

  void Kill() {
    const TaskHandle_t handle = handle_.exchange(nullptr);
    if (handle) {
      vTaskDelete(handle);
    }
  }

 private:
  std::atomic<TaskHandle_t> handle_ = nullptr;

  Task(const Task&) = delete;
  Task(Task&&) = delete;
  Task& operator=(const Task&) = delete;
  static void RunAdapter(void* self) { reinterpret_cast<Task*>(self)->Run(); }
};
