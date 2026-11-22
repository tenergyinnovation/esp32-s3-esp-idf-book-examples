/*
 * บทที่ 13 ตัวอย่าง 1: NVS (Non-Volatile Storage)
 * เก็บตัวนับไว้ใน Flash ด้วยคู่ "กุญแจ-ค่า" namespace "app" key "boot_cnt"
 */
#include <inttypes.h>
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

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
    nvs_handle_t h;
    ESP_ERROR_CHECK(nvs_open("app", NVS_READWRITE, &h));

    uint32_t count = 0;
    esp_err_t err = nvs_get_u32(h, "boot_cnt", &count);
    if (err == ESP_ERR_NVS_NOT_FOUND) ESP_LOGI("nvs", "ยังไม่เคยบันทึก เริ่มนับจาก 0");
    else ESP_ERROR_CHECK(err);

    count++;
    ESP_ERROR_CHECK(nvs_set_u32(h, "boot_cnt", count));
    ESP_ERROR_CHECK(nvs_commit(h));                 /* commit = ยืนยันเขียนลง Flash จริง */
    nvs_close(h);
    ESP_LOGI("nvs", "เปิดเครื่องครั้งที่ %" PRIu32 " (กด RST หรือถอดปลั๊กแล้วเสียบใหม่ ตัวเลขจะเพิ่ม)", count);
}
