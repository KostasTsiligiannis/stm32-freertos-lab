#include "led_controller.h"

uint32_t LedController_GetBlinkPeriodMs(SystemMode_t mode)
{
    if (mode == SYS_MODE_ALERT) {
        return 100U;
    }
    return 500U;
}
