/*
 * บทที่ 9 ตัวอย่าง 6: SPI loopback
 * ต่อสาย GPIO11 (MOSI) เข้า GPIO13 (MISO) ข้อมูลที่ส่งออกจะวนกลับเข้ามา
 * ใช้ตรวจว่า SPI bus และสายทำงานก่อนต่ออุปกรณ์จริง
 */
#include <string.h>
#include "driver/spi_master.h"
#include "esp_log.h"

void app_main(void)
{
    spi_bus_config_t bus = { .mosi_io_num = 11, .miso_io_num = 13, .sclk_io_num = 12,
                             .quadwp_io_num = -1, .quadhd_io_num = -1, .max_transfer_sz = 64 };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &bus, SPI_DMA_CH_AUTO));
    spi_device_interface_config_t dev = { .clock_speed_hz = 1 * 1000 * 1000, .mode = 0,
                                          .spics_io_num = 10, .queue_size = 1 };
    spi_device_handle_t h;
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &dev, &h));

    uint8_t tx[16] = "ESP32-S3 SPI OK", rx[16] = { 0 };
    spi_transaction_t t = { .length = sizeof(tx) * 8, .tx_buffer = tx, .rx_buffer = rx };
    ESP_ERROR_CHECK(spi_device_transmit(h, &t));
    ESP_LOGI("spi", "ส่ง: %s", tx);
    ESP_LOGI("spi", "รับ: %s", rx);
    ESP_LOGI("spi", "ผล: %s", memcmp(tx, rx, sizeof(tx)) == 0 ? "ตรงกัน สาย SPI ปกติ" : "ไม่ตรง ตรวจสาย MOSI-MISO");
}
