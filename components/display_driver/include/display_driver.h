#pragma once
#include <string.h>
#include <stdio.h>
#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_timer.h"
// Display connect to master bus
#include "driver/i2c_master.h"
// Displays common
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
// My implementation of most common functions
#include "lvgl_driver.h"            // LVGL required for most displays

// Pins
#define I2C_PORT                    0
#define DISP_I2C_SDA                CONFIG_COMMON_SDA_PIN
#define DISP_I2C_SCL                CONFIG_COMMON_SCL_PIN
#define DISP_I2C_ADR                CONFIG_DISP_I2C_ADR

#define LCD_PIXEL_CLOCK_HZ          (400 * 1000)
#define DISP_I2C_RST                -1
// Bit number used to represent command and parameter
#define LCD_CMD_BITS                8
#define LCD_PARAM_BITS              8

/* LCD size SSD1306 */
#define DISP_HOR_RES                128
#define DISP_VER_RES                64

// Common handles for any display
extern esp_lcd_panel_handle_t       panel_handle;
extern esp_lcd_panel_io_handle_t    io_handle;


esp_err_t display_init(void);
// Do not use other functions out of this module.