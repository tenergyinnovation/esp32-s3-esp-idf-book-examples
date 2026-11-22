/*
 * บทที่ 17 ตัวอย่าง 2: USB HID Keyboard
 * กดปุ่ม BOOT (GPIO0) แล้วบอร์ดจะ "พิมพ์" ข้อความ Hello ESP32-S3 ลงในโปรแกรมที่เปิดอยู่บนคอมพิวเตอร์
 * ไม่ต้องลงไดรเวอร์ เพราะคีย์บอร์ดเป็นอุปกรณ์มาตรฐาน (HID class)
 * ข้อควรระวัง: ก่อนกดปุ่ม ให้เปิดโปรแกรมแก้ไขข้อความเปล่าๆ รอไว้
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "tinyusb.h"
#include "tinyusb_default_config.h"
#include "class/hid/hid_device.h"
#include "esp_log.h"

#define BTN_GPIO GPIO_NUM_0
static const char *TAG = "hid";

/* report descriptor = "แบบฟอร์ม" ที่บอกคอมพิวเตอร์ว่าข้อมูลแต่ละไบต์หมายถึงอะไร */
static const uint8_t s_report_desc[] = { TUD_HID_REPORT_DESC_KEYBOARD() };
static const char *s_strings[] = { (char[]){ 0x09, 0x04 }, "Tenergy", "ESP32-S3 Keyboard", "000001", "HID Keyboard" };
#define CFG_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)
static const uint8_t s_config_desc[] = {
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, CFG_LEN, 0, 100),                              // 1 interface, ขอไฟ 100 mA
    TUD_HID_DESCRIPTOR(0, 4, HID_ITF_PROTOCOL_KEYBOARD, sizeof(s_report_desc), 0x81, 8, 10),  // ส่งทุก 10 ms
};

/* TinyUSB เรียก callback เหล่านี้ ต้องมีให้ครบแม้ไม่ได้ใช้ */
uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance) { return s_report_desc; }
uint16_t tud_hid_get_report_cb(uint8_t i, uint8_t id, hid_report_type_t t, uint8_t *buf, uint16_t len) { return 0; }
void tud_hid_set_report_cb(uint8_t i, uint8_t id, hid_report_type_t t, uint8_t const *buf, uint16_t len) {}

/* แปลงตัวอักษร ASCII เป็น keycode + modifier (รองรับเฉพาะ a-z A-Z 0-9 ช่องว่าง และ -) */
static bool ascii_to_key(char c, uint8_t *key, uint8_t *mod)
{
    *mod = 0;
    if (c >= 'a' && c <= 'z') { *key = HID_KEY_A + (c - 'a'); return true; }
    if (c >= 'A' && c <= 'Z') { *key = HID_KEY_A + (c - 'A'); *mod = KEYBOARD_MODIFIER_LEFTSHIFT; return true; }
    if (c >= '1' && c <= '9') { *key = HID_KEY_1 + (c - '1'); return true; }
    if (c == '0') { *key = HID_KEY_0; return true; }
    if (c == ' ') { *key = HID_KEY_SPACE; return true; }
    if (c == '-') { *key = HID_KEY_MINUS; return true; }
    if (c == '\n') { *key = HID_KEY_ENTER; return true; }
    return false;
}

static void type_text(const char *s)
{
    for (; *s; s++) {
        uint8_t key, mod;
        if (!ascii_to_key(*s, &key, &mod)) continue;
        uint8_t keys[6] = { key };
        while (!tud_hid_ready()) vTaskDelay(1);
        tud_hid_keyboard_report(0, mod, keys);            // กด
        vTaskDelay(pdMS_TO_TICKS(15));
        while (!tud_hid_ready()) vTaskDelay(1);
        tud_hid_keyboard_report(0, 0, NULL);              // ปล่อย (ถ้าไม่ปล่อย คอมพิวเตอร์จะคิดว่ากดค้าง)
        vTaskDelay(pdMS_TO_TICKS(15));
    }
}

void app_main(void)
{
    gpio_config_t io = { .pin_bit_mask = 1ULL << BTN_GPIO, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    ESP_ERROR_CHECK(gpio_config(&io));

    tinyusb_config_t cfg = TINYUSB_DEFAULT_CONFIG();
    cfg.descriptor.device = NULL;                             // ใช้ device descriptor มาตรฐาน
    cfg.descriptor.full_speed_config = s_config_desc;
    cfg.descriptor.string = s_strings;
    cfg.descriptor.string_count = sizeof(s_strings) / sizeof(s_strings[0]);
    ESP_ERROR_CHECK(tinyusb_driver_install(&cfg));
    ESP_LOGI(TAG, "เป็นคีย์บอร์ดแล้ว กดปุ่ม BOOT เพื่อพิมพ์ข้อความ");

    while (1) {
        if (gpio_get_level(BTN_GPIO) == 0 && tud_mounted()) {
            ESP_LOGI(TAG, "กำลังพิมพ์...");
            type_text("Hello ESP32-S3 from Tenergy\n");
            while (gpio_get_level(BTN_GPIO) == 0) vTaskDelay(pdMS_TO_TICKS(20));   // รอปล่อยปุ่ม
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
