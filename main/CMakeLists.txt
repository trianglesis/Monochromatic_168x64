idf_component_register(SRCS "main.c"
                    PRIV_REQUIRES spi_flash
                    REQUIRES display_driver lvgl_driver
                    INCLUDE_DIRS "")
