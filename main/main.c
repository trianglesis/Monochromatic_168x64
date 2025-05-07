#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "display_driver.h"

static const char *TAG = "mono-lvgl";

void app_main(void)
{
    ESP_LOGI(TAG, "Start display test")
    vTaskDelay(1000/portTICK_PERIOD_MS);

    ESP_ERROR_CHECK(display_init());
    TaskHandle_t taskHandle = NULL;

    BaseType_t res = xTaskCreatePinnedToCore(lvgl_task_i2c, "LVGL task", 8192, NULL, 4, &taskHandle, 0); // stack, params, prio, handle, core
    while(true) {
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
    
}
