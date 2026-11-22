/*
 * บทที่ 15 ตัวอย่าง 4: unit test ด้วย Unity (มากับ ESP-IDF)
 * ทดสอบฟังก์ชัน fan_decide() ในหลายสถานการณ์ ทุก test ต้องผ่านก่อนปล่อย firmware
 */
#include "unity.h"
#include "fan_logic.h"

void setUp(void) {}
void tearDown(void) {}

static void test_cold_stays_off(void)        { TEST_ASSERT_FALSE(fan_decide(false, 25.0f)); }
static void test_hot_turns_on(void)          { TEST_ASSERT_TRUE(fan_decide(false, 32.0f)); }
static void test_hysteresis_keeps_on(void)   { TEST_ASSERT_TRUE(fan_decide(true, 31.0f)); }
static void test_hysteresis_turns_off(void)  { TEST_ASSERT_FALSE(fan_decide(true, 30.0f)); }
static void test_invalid_sensor_failsafe(void) { TEST_ASSERT_TRUE(fan_decide(false, -999.0f)); }

void app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_cold_stays_off);
    RUN_TEST(test_hot_turns_on);
    RUN_TEST(test_hysteresis_keeps_on);
    RUN_TEST(test_hysteresis_turns_off);
    RUN_TEST(test_invalid_sensor_failsafe);
    UNITY_END();
}
