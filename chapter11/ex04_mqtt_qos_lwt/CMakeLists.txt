# ESP-IDF v6.1 · target esp32s3 · หนังสือ "คู่มือการพัฒนา ESP32-S3 ด้วย ESP-IDF v6.1 และ VS Code"
cmake_minimum_required(VERSION 3.22)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
idf_build_set_property(MINIMAL_BUILD ON)
project(ex04_mqtt_qos_lwt)
