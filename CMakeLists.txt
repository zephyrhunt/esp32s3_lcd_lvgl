cmake_minimum_required(VERSION 3.16)

include($ENV{ADF_PATH}/CMakeLists.txt)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

add_compile_definitions(LV_LVGL_H_INCLUDE_SIMPLE)
project(lv8_lcd18)
