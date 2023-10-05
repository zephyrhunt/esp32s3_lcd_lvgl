
set(include_dirs .)

idf_component_register(SRC_DIRS .
                       INCLUDE_DIRS .
                       REQUIRES driver lvgl spi_lcd led_strip)
