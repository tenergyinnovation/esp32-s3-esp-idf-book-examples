/*
 * บทที่ 4 ตัวอย่าง 5: esp_err_t
 * เทียบ 3 วิธี: ตรวจเอง, ESP_ERROR_CHECK, ESP_RETURN_ON_ERROR
 */
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "driver/gpio.h"

static const char *TAG = "errors";

// ฟังก์ชันที่ "อาจล้มเหลว" ควรคืน esp_err_t ให้ผู้เรียกตัดสินใจ
static esp_err_t setup_fan_pin(gpio_num_t pin)
{
    ESP_RETURN_ON_FALSE(GPIO_IS_VALID_OUTPUT_GPIO(pin), ESP_ERR_INVALID_ARG, TAG, "GPIO%d ใช้เป็น output ไม่ได้", pin);
    ESP_RETURN_ON_ERROR(gpio_reset_pin(pin), TAG, "reset GPIO%d ไม่สำเร็จ", pin);
    ESP_RETURN_ON_ERROR(gpio_set_direction(pin, GPIO_MODE_OUTPUT), TAG, "ตั้ง output ไม่สำเร็จ");
    return ESP_OK;
}

void app_main(void)
{
    // วิธีที่ 1: ตรวจเองแล้วตัดสินใจ (ระบบทำงานต่อได้)
    esp_err_t err = setup_fan_pin(GPIO_NUM_6);
    ESP_LOGI(TAG, "GPIO6 -> %s", esp_err_to_name(err));

    err = setup_fan_pin((gpio_num_t)99);           // ขาไม่มีจริง
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "GPIO99 -> %s : ใช้ค่าสำรองแทน", esp_err_to_name(err));
    }

    // วิธีที่ 2: ESP_ERROR_CHECK ใช้กับขั้นที่ "ต้องสำเร็จเท่านั้น"
    // ถ้าล้มเหลว โปรแกรมจะหยุด (abort) แล้วรีสตาร์ต พร้อมบอกบรรทัดที่ผิด
    ESP_ERROR_CHECK(setup_fan_pin(GPIO_NUM_7));
    ESP_LOGI(TAG, "ตั้งค่าสำเร็จทั้งหมด");
}
