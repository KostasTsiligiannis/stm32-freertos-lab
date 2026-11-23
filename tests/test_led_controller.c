#include "unity.h"
#include "led_controller.h"

void setUp(void) {}
void tearDown(void) {}

void test_NormalMode_ShouldReturn500ms(void)
{
    TEST_ASSERT_EQUAL_UINT32(500U, LedController_GetBlinkPeriodMs(SYS_MODE_NORMAL));
}

void test_AlertMode_ShouldReturn100ms(void)
{
    TEST_ASSERT_EQUAL_UINT32(100U, LedController_GetBlinkPeriodMs(SYS_MODE_ALERT));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_NormalMode_ShouldReturn500ms);
    RUN_TEST(test_AlertMode_ShouldReturn100ms);
    return UNITY_END();
}
