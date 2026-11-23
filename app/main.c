#include "stm32f3xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led_controller.h"

static void GPIO_Init(void);
static void vTaskLedStatus(void *pvParameters);

int main(void)
{
    HAL_Init();
    GPIO_Init();

    xTaskCreate(vTaskLedStatus, "LED_Status", 128, NULL, 2, NULL);
    vTaskStartScheduler();

    while (1)
    {
    }
}

static void vTaskLedStatus(void *pvParameters)
{
    (void)pvParameters;
    uint32_t delay_ms = LedController_GetBlinkPeriodMs(SYS_MODE_NORMAL);

    for (;;)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

static void GPIO_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
