#pragma once
#include <stdbool.h>
/* ตัดสินใจเปิด/ปิดพัดลม: เปิดที่ >= 32 C ปิดที่ <= 30 C ค่าเซนเซอร์ผิดปกติ -> เปิด (fail-safe) */
bool fan_decide(bool fan_now, float temp_c);
