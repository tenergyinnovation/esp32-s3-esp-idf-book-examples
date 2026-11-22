/*
 * บทที่ 9 ตัวอย่าง 3: จอ OLED SSD1306 128x64 (I2C 0x3C)
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "oled.h"

static i2c_master_bus_handle_t i2c_bus_start(void)
{
    i2c_master_bus_config_t cfg = {
        .i2c_port = I2C_NUM_0, .sda_io_num = 8, .scl_io_num = 9,     /* SDA=GPIO8, SCL=GPIO9 */
        .clk_source = I2C_CLK_SRC_DEFAULT, .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,                       /* โมดูลส่วนใหญ่มี pull-up ภายนอกแล้ว */
    };
    i2c_master_bus_handle_t bus;
    ESP_ERROR_CHECK(i2c_new_master_bus(&cfg, &bus));
    return bus;
}

void app_main(void)
{
    i2c_master_bus_handle_t bus = i2c_bus_start();
    ESP_ERROR_CHECK(oled_init(bus, 0x3C));
    for (int sec = 0; ; sec++) {
        char line[24];
        oled_clear();
        oled_rect(0, 0, 128, 64, false);              // กรอบรอบจอ
        oled_text(6, 1, "Tenergy Innovation");
        oled_text(6, 3, "ESP32-S3 + OLED");
        snprintf(line, sizeof(line), "%03d", sec);
        oled_text_big(46, 5, line);
        ESP_ERROR_CHECK(oled_flush());
        ESP_LOGI("oled", "แสดงวินาทีที่ %d", sec);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
