#pragma once
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/lock.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
// #include "ui.h"
// Use display, we need panel_handle and io_handle
#include "display_driver.h"


#ifdef CONFIG_LV_CONF_SKIP
#else
// CUSTOM configured. Do not use now, use Kconfig
#include "lvgl.h"
#endif  // LVGL

#define LVGL_TICK_PERIOD_MS     5
#define LVGL_TASK_STACK_SIZE    (4 * 1024)
#define LVGL_TASK_PRIORITY      2
#define LVGL_PALETTE_SIZE       8
#define LVGL_TASK_MAX_DELAY_MS  500
#define LVGL_TASK_MIN_DELAY_MS  1000 / CONFIG_FREERTOS_HZ

#define DISPLAY_UPDATE_FREQ     1000
#define BUFFER_SIZE             (DISP_HOR_RES * DISP_VER_RES / 8)
#define RENDER_MODE             LV_DISPLAY_RENDER_MODE_FULL

// Use offset only for I2C
#ifdef CONFIG_ROTATE_0
#define ROTATE_DEGREE           0
#define Offset_X                0
#define Offset_Y                0
#elif CONFIG_ROTATE_90
#define ROTATE_DEGREE           90
#define Offset_X                0
#define Offset_Y                0
#elif CONFIG_ROTATE_180
#define ROTATE_DEGREE           180
#define Offset_X                0
#define Offset_Y                0
#elif CONFIG_ROTATE_270
#define ROTATE_DEGREE           270
#define Offset_X                0
#define Offset_Y                0
#else
#define ROTATE_DEGREE           0
#define Offset_X                0
#define Offset_Y                0
#endif // CONFIG_ROTATE

// Save display when init and use it all over the project
extern lv_disp_t *display; 

esp_err_t lvgl_init(void);
void graphics_i2c_draw(void);
// Do not use other functions out of this module.