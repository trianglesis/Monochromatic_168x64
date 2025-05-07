#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "display_driver.h"

static const char *TAG = "mono-lvgl";

void app_main(void)
{
    vTaskDelay(pdMS_TO_TICKS(500));
    ESP_ERROR_CHECK(display_init());
    ESP_LOGI(TAG, "Init display");
    vTaskDelay(pdMS_TO_TICKS(500));
}
