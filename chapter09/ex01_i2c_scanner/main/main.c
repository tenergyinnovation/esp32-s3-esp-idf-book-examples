/*
 * บทที่ 9 ตัวอย่าง 1: I2C scanner
 * "เคาะประตู" ทุก address 0x08..0x77 ใครตอบ (ACK) แปลว่ามีอุปกรณ์อยู่
 * SDA=GPIO8, SCL=GPIO9
 */
#include "driver/i2c_master.h"
#include "esp_log.h"

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
    int found = 0;
    ESP_LOGI("scan", "เริ่มสแกน I2C...");
    for (uint8_t addr = 0x08; addr <= 0x77; addr++) {
        if (i2c_master_probe(bus, addr, 50) == ESP_OK) {
            const char *hint = addr == 0x3C ? " (จอ OLED SSD1306)" : addr == 0x44 ? " (SHT31)" : "";
            ESP_LOGI("scan", "พบอุปกรณ์ที่ 0x%02X%s", addr, hint);
            found++;
        }
    }
    ESP_LOGI("scan", "สแกนเสร็จ พบทั้งหมด %d ตัว", found);
}
