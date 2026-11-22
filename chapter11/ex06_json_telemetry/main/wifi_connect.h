/* wifi_connect.h — เชื่อมต่อ Wi-Fi แบบ station พร้อม reconnect อัตโนมัติ */
#pragma once
#include "esp_err.h"
#include "freertos/FreeRTOS.h"

/* เริ่ม Wi-Fi แล้วรอจนได้ IP หรือหมดเวลา */
esp_err_t wifi_connect(TickType_t timeout);
bool      wifi_is_connected(void);
