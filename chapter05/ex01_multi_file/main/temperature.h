/* temperature.h — "เมนูร้านอาหาร": บอกว่ามีฟังก์ชันอะไรให้เรียก */
#pragma once
#include <stdbool.h>

#define TEMP_HOT_THRESHOLD_C 30.0f

float temp_c_to_f(float celsius);
bool  temp_is_hot(float celsius);
