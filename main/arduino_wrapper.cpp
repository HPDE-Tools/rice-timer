#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "Arduino.h"
#if ARDUINO_SERIAL_PORT //Serial used for USB CDC
#include "USB.h"
#endif

TaskHandle_t loopTaskHandle = NULL;

#if CONFIG_FREERTOS_UNICORE
void yieldIfNecessary(void){
    static uint64_t lastYield = 0;
    uint64_t now = millis();
    if((now - lastYield) > 2000) {
        lastYield = now;
        vTaskDelay(5); //delay 1 RTOS tick
    }
}
#endif

bool loopTaskWDTEnabled;

void setup(void);
void loop(void);

void loopTask(void *pvParameters)
{
    setup();
    for(;;) {
#if CONFIG_FREERTOS_UNICORE
        yieldIfNecessary();
#endif
        if(loopTaskWDTEnabled){
            esp_task_wdt_reset();
        }
        loop();
        if (serialEventRun) serialEventRun();
    }
}

extern "C" void app_main()
{
#if ARDUINO_SERIAL_PORT //Serial used for USB CDC
    USB.begin();
#endif
    loopTaskWDTEnabled = false;
    initArduino();
    xTaskCreateUniversal(loopTask, "loopTask", 8192, NULL, 1, &loopTaskHandle, ARDUINO_RUNNING_CORE);
}

