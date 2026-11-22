/*
 * บทที่ 9 ตัวอย่าง 2: เซนเซอร์ SHT31 (I2C address 0x44)
 * อ่านทุก 2 วินาที ตรวจ CRC ทุกครั้ง ถ้าอ่านพลาด 3 ครั้งติดกันแจ้งว่าเซนเซอร์เสีย
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "sht31.h"

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
    ESP_ERROR_CHECK(sht31_init(bus, 0x44));
    int fails = 0;
    while (1) {
        float t, rh;
        esp_err_t err = sht31_read(&t, &rh);
        if (err == ESP_OK) {
            fails = 0;
            ESP_LOGI("sht31", "อุณหภูมิ %.2f C  ความชื้น %.1f %%RH", t, rh);
        } else if (++fails >= 3) {
            ESP_LOGE("sht31", "อ่านไม่ได้ %d ครั้งติด (%s) ตรวจสายไฟ", fails, esp_err_to_name(err));
        } else {
            ESP_LOGW("sht31", "อ่านพลาด (%s) ลองใหม่", esp_err_to_name(err));
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
