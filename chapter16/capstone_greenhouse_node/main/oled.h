/* oled.h — ไดรเวอร์จอ OLED SSD1306 128x64 แบบง่าย (ใช้ esp_lcd ของ ESP-IDF) */
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "driver/i2c_master.h"
#include "esp_err.h"

#define OLED_W 128
#define OLED_H 64

esp_err_t oled_init(i2c_master_bus_handle_t bus, uint8_t addr);
void oled_clear(void);
void oled_pixel(int x, int y, bool on);
void oled_text(int x, int page, const char *s);          /* page = แถวละ 8 pixel (0..7) */
void oled_text_big(int x, int page, const char *s);      /* ตัวอักษรขยาย 2 เท่า สูง 2 page */
void oled_rect(int x, int y, int w, int h, bool fill);
esp_err_t oled_flush(void);                              /* ส่ง buffer ขึ้นจอ */
