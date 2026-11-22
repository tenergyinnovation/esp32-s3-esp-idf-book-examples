#include "fan_logic.h"

bool fan_decide(bool fan_now, float temp_c)
{
    if (temp_c < -40.0f || temp_c > 85.0f) return true;     /* นอกช่วงที่เซนเซอร์วัดได้ = เสีย */
    if (fan_now) return temp_c > 30.0f;
    return temp_c >= 32.0f;
}
