set(srcs "spi_lcd.c")

set(include_dirs .)

idf_component_register(SRC_DIRS .
                       INCLUDE_DIRS .
                       REQUIRES driver )
