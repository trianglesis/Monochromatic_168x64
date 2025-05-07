#include <stdio.h>
#include "display_driver.h"

static const char *TAG = "oled-display-i2c";


/*
    Common for all displays
*/
esp_lcd_panel_handle_t panel_handle;
esp_lcd_panel_io_handle_t io_handle;

static void display_driver_info(void) {
    printf(" - Init: display_driver_info empty function call!\n\n");
    ESP_LOGI(TAG, "DISP_I2C_SDA: %d", DISP_I2C_SDA);
    ESP_LOGI(TAG, "DISP_I2C_SCL: %d", DISP_I2C_SCL);
    ESP_LOGI(TAG, "DISP_I2C_ADR: 0x%x", DISP_I2C_ADR);
    ESP_LOGI(TAG, "DISP_HOR_RES: %d", DISP_HOR_RES);
    ESP_LOGI(TAG, "DISP_VER_RES: %d", DISP_VER_RES);
}

/*
INIT Master Bus here. 
But it can be moved into separate module
*/
static esp_err_t display_i2c_init(void) {
    ESP_LOGI(TAG, "Run display i2c setup.");
    i2c_master_bus_handle_t bus_handle = NULL;
    // New I2C bus setup, new driver used, from IDF 5.4+
    i2c_master_bus_config_t bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_PORT,
        .scl_io_num = DISP_I2C_SCL,
        .sda_io_num = DISP_I2C_SDA,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));
    // Test device address, fail if connection is bad or pins are wrong!
    ESP_ERROR_CHECK(i2c_master_probe(bus_handle, DISP_I2C_ADR, 50)); // Wait 50 ms

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = DISP_I2C_ADR,
        .scl_speed_hz = LCD_PIXEL_CLOCK_HZ,
        .control_phase_bytes = 1,               // According to SSD1306 datasheet
        .lcd_cmd_bits = LCD_CMD_BITS,           // According to SSD1306 datasheet
        .lcd_param_bits = LCD_CMD_BITS,         // According to SSD1306 datasheet
        .dc_bit_offset = 6,                     // According to SSD1306 datasheet
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(bus_handle, &io_config, &io_handle));

    ESP_LOGI(TAG, "Install SSD1306 panel driver");
    esp_lcd_panel_dev_config_t panel_config = {
        .bits_per_pixel = 1,
        .reset_gpio_num = DISP_I2C_RST,
    };
    esp_lcd_panel_ssd1306_config_t ssd1306_config = {
        .height = DISP_VER_RES,
    };
    panel_config.vendor_config = &ssd1306_config;
    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io_handle, &panel_config, &panel_handle));
    
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
    ESP_LOGI(TAG, "Display panel installed!");
    return ESP_OK;
}

esp_err_t display_init(void) {
    display_driver_info();  // Debug info print
    display_i2c_init();  // Init as I2C
    ESP_LOGI(TAG, "LVGL Display graphics initialization!");
    ESP_ERROR_CHECK(lvgl_init());  // Init LVGL for display and later use it

    graphics_i2c_draw();

    return ESP_OK;
}