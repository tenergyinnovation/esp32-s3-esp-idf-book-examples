#include "sht31.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static i2c_master_dev_handle_t s_dev;

static uint8_t crc8_sht(const uint8_t *d, int n)     /* พหุนาม 0x31 ค่าเริ่ม 0xFF ตาม datasheet */
{
    uint8_t crc = 0xFF;
    for (int i = 0; i < n; i++) {
        crc ^= d[i];
        for (int b = 0; b < 8; b++) crc = (crc & 0x80) ? (uint8_t)((crc << 1) ^ 0x31) : (uint8_t)(crc << 1);
    }
    return crc;
}

esp_err_t sht31_init(i2c_master_bus_handle_t bus, uint8_t addr)
{
    i2c_device_config_t cfg = { .dev_addr_length = I2C_ADDR_BIT_LEN_7, .device_address = addr, .scl_speed_hz = 100000 };
    return i2c_master_bus_add_device(bus, &cfg, &s_dev);
}

esp_err_t sht31_read(float *temp_c, float *rh)
{
    const uint8_t cmd[2] = { 0x24, 0x00 };             /* single shot, high repeatability */
    uint8_t d[6];
    esp_err_t err = i2c_master_transmit(s_dev, cmd, 2, 100);
    if (err != ESP_OK) return err;
    vTaskDelay(pdMS_TO_TICKS(20));                     /* รอวัด ~15 ms */
    err = i2c_master_receive(s_dev, d, 6, 100);
    if (err != ESP_OK) return err;
    if (crc8_sht(d, 2) != d[2] || crc8_sht(d + 3, 2) != d[5]) return ESP_ERR_INVALID_CRC;
    uint16_t t = (d[0] << 8) | d[1], h = (d[3] << 8) | d[4];
    *temp_c = -45.0f + 175.0f * t / 65535.0f;
    *rh = 100.0f * h / 65535.0f;
    return ESP_OK;
}
