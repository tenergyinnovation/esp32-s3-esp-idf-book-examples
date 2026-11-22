/* sht31.h — อ่านเซนเซอร์ SHT31 ผ่าน I2C (address 0x44) */
#pragma once
#include "driver/i2c_master.h"
#include "esp_err.h"

esp_err_t sht31_init(i2c_master_bus_handle_t bus, uint8_t addr);
/* คืน ESP_ERR_INVALID_CRC ถ้าข้อมูลเสีย */
esp_err_t sht31_read(float *temp_c, float *rh);
