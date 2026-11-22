/*
 * บทที่ 4 ตัวอย่าง 7: stack, static, heap และ PSRAM
 */
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "esp_heap_caps.h"
#include "esp_memory_utils.h"
#include "esp_log.h"

static const char *TAG = "memory";
static uint8_t s_static_buf[1024];          // .bss ใน SRAM ภายใน

static void show(const char *what, const void *p)
{
    const char *where = esp_ptr_external_ram(p) ? "PSRAM" :
                        esp_ptr_internal(p)     ? "SRAM ภายใน" : "Flash/อื่นๆ";
    ESP_LOGI(TAG, "%-22s %p  -> %s", what, p, where);
}

void app_main(void)
{
    uint8_t stack_buf[64];                   // อยู่บน stack ของ task
    static const char k_msg[] = "hello";     // อยู่ใน Flash (.rodata)

    uint8_t *heap_buf  = malloc(4096);       // heap ปกติ
    uint8_t *big_buf   = heap_caps_malloc(512 * 1024, MALLOC_CAP_SPIRAM);  // 512 KB ใน PSRAM

    show("stack_buf[64]", stack_buf);
    show("s_static_buf[1024]", s_static_buf);
    show("k_msg (const)", k_msg);
    show("malloc(4096)", heap_buf);
    if (big_buf) show("PSRAM 512 KB", big_buf);
    else ESP_LOGW(TAG, "จอง PSRAM ไม่ได้ (ไม่มี PSRAM)");

    ESP_LOGI(TAG, "heap ภายในว่าง: %u bytes", (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    ESP_LOGI(TAG, "PSRAM ว่าง:    %u bytes", (unsigned)heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

    free(heap_buf);          // คืนหน่วยความจำทุกครั้งที่ใช้เสร็จ
    free(big_buf);
}
