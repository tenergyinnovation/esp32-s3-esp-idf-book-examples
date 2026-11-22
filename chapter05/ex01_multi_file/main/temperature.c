/* temperature.c — "ห้องครัว": วิธีทำจริงของแต่ละฟังก์ชัน */
#include "temperature.h"

float temp_c_to_f(float celsius)
{
    return celsius * 9.0f / 5.0f + 32.0f;
}

bool temp_is_hot(float celsius)
{
    return celsius > TEMP_HOT_THRESHOLD_C;
}
