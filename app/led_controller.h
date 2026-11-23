#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <stdint.h>

typedef enum {
    SYS_MODE_NORMAL = 0,
    SYS_MODE_ALERT  = 1
} SystemMode_t;

uint32_t LedController_GetBlinkPeriodMs(SystemMode_t mode);

#endif /* LED_CONTROLLER_H */
