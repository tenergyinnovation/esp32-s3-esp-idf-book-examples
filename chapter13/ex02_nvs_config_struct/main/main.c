/*
 * บทที่ 13 ตัวอย่าง 2: เก็บ struct ทั้งก้อนด้วย nvs_set_blob
 * มีเลขเวอร์ชันในข้อมูล ถ้าอัปเดต firmware แล้วโครงสร้างเปลี่ยน จะรู้และใช้ค่าเริ่มต้นแทน
 */
#include <string.h>
#include <stdint.h>
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

#define CFG_VERSION 2
typedef struct {
    uint16_t version;
    char     name[24];
    int16_t  fan_on_c10;        /* อุณหภูมิเปิดพัดลม x10 เช่น 320 = 32.0 C */
    int16_t  fan_off_c10;
    uint16_t report_s;          /* ส่งข้อมูลทุกกี่วินาที */
} app_cfg_t;

static const app_cfg_t DEFAULTS = { .version = CFG_VERSION, .name = "Greenhouse-A",
                                    .fan_on_c10 = 320, .fan_off_c10 = 300, .report_s = 60 };
static const char *TAG = "cfg";

static void nvs_init_safe(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());       /* พื้นที่ NVS เต็มหรือรูปแบบเก่า -> ล้างแล้วเริ่มใหม่ */
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}

static void cfg_load(app_cfg_t *c)
{
    nvs_handle_t h; size_t len = sizeof(*c);
    *c = DEFAULTS;
    if (nvs_open("cfg", NVS_READONLY, &h) != ESP_OK) { ESP_LOGW(TAG, "ยังไม่มีค่าตั้ง ใช้ค่าเริ่มต้น"); return; }
    app_cfg_t tmp;
    esp_err_t err = nvs_get_blob(h, "main", &tmp, &len);
    nvs_close(h);
    if (err != ESP_OK || len != sizeof(tmp) || tmp.version != CFG_VERSION) {
        ESP_LOGW(TAG, "ค่าตั้งเดิมใช้ไม่ได้ (err=%s, version=%u) ใช้ค่าเริ่มต้น", esp_err_to_name(err), err == ESP_OK ? tmp.version : 0);
        return;
    }
    *c = tmp;
}

static esp_err_t cfg_save(const app_cfg_t *c)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open("cfg", NVS_READWRITE, &h);
    if (err != ESP_OK) return err;
    err = nvs_set_blob(h, "main", c, sizeof(*c));
    if (err == ESP_OK) err = nvs_commit(h);
    nvs_close(h);
    return err;
}

void app_main(void)
{
    nvs_init_safe();
    app_cfg_t cfg;
    cfg_load(&cfg);
    ESP_LOGI(TAG, "ค่าปัจจุบัน: %s เปิด %.1f C ปิด %.1f C รายงานทุก %u s",
             cfg.name, cfg.fan_on_c10 / 10.0f, cfg.fan_off_c10 / 10.0f, cfg.report_s);
    cfg.fan_on_c10 += 5;               /* จำลองผู้ใช้ปรับค่าเพิ่ม 0.5 C */
    ESP_ERROR_CHECK(cfg_save(&cfg));
    ESP_LOGI(TAG, "บันทึกแล้ว รีเซ็ตบอร์ดเพื่อดูค่าที่จำไว้");
}
