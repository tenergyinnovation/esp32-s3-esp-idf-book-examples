/*
 * บทที่ 13 ตัวอย่าง 5: factory reset
 * ใช้ปุ่ม BOOT (GPIO0) บนบอร์ด: หลังบูตเสร็จแล้ว กดค้าง 3 วินาที -> ล้าง NVS ทั้งหมด แล้วรีสตาร์ต
 * (GPIO0 เป็น strapping pin จึงอ่านปุ่มหลังบูตเท่านั้น ห้ามกดค้างตอนกด RST)
 */
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_system.h"
#include "esp_log.h"

#define BTN GPIO_NUM_0
#define HOLD_MS 3000
static const char *TAG = "reset";

static void nvs_init_safe(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());       /* พื้นที่ NVS เต็มหรือรูปแบบเก่า -> ล้างแล้วเริ่มใหม่ */
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}

void app_main(void)
{
    nvs_init_safe();
    nvs_handle_t h; uint32_t boots = 0;
    nvs_open("app", NVS_READWRITE, &h);
    nvs_get_u32(h, "boot_cnt", &boots);
    nvs_set_u32(h, "boot_cnt", ++boots); nvs_commit(h); nvs_close(h);
    ESP_LOGI(TAG, "บูตครั้งที่ %" PRIu32 "  กด BOOT ค้าง 3 วินาทีเพื่อล้างค่า", boots);

    gpio_config_t in = { .pin_bit_mask = 1ULL << BTN, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    ESP_ERROR_CHECK(gpio_config(&in));
    int held = 0;
    while (1) {
        held = gpio_get_level(BTN) == 0 ? held + 100 : 0;
        if (held > 0 && held % 1000 == 0 && held < HOLD_MS) ESP_LOGW(TAG, "กดค้าง %d วินาที...", held / 1000);
        if (held >= HOLD_MS) {
            ESP_LOGE(TAG, "ล้างค่าทั้งหมดและรีสตาร์ต");
            ESP_ERROR_CHECK(nvs_flash_erase());
            vTaskDelay(pdMS_TO_TICKS(200));
            esp_restart();
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
