idf_build_get_property(target IDF_TARGET)

set(srcs "display_driver.c")
set(requires "driver" "esp_timer" "esp_lcd")
set(priv_requires "")
set(include_dirs "include")

idf_component_register(
                        SRCS        "${srcs}"
                        REQUIRES    "${requires}" 
                                    "lvgl_driver" 
                        PRIV_REQUIRES "${priv_requires}"
                        INCLUDE_DIRS "${include_dirs}"
)

# message("CONFIG_CONNECTION_SPI   'display_driver':         ${CONFIG_CONNECTION_SPI}")
# message("CONFIG_CONNECTION_I2C   'display_driver':         ${CONFIG_CONNECTION_I2C}")
# message("REQUIRES                'display_driver':         ${requires}")
# message("PRIV_REQUIRES           'display_driver':         ${priv_requires}")