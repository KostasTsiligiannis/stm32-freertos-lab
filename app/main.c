#include "stm32f3xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

static void GPIO_Init(void);
static void vTaskLedFast(void *pvParameters);
static void vTaskLedSlow(void *pvParameters);

int main(void)
{
    HAL_Init();
    GPIO_Init();

    /* Δημιουργία 2 Tasks όπως στο πρώτο εργαστήριο του μαθήματος */
    xTaskCreate(vTaskLedFast, "LED_Task1", 128, NULL, 2, NULL);
    xTaskCreate(vTaskLedSlow, "LED_Task2", 128, NULL, 1, NULL);

    /* Εκκίνηση του FreeRTOS Scheduler */
    vTaskStartScheduler();

    while (1)
    {
    }
}

static void vTaskLedFast(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

static void vTaskLedSlow(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void GPIO_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_3; /* LD3 Green LED στη Nucleo-F303K8 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* Απαραίτητος ISR για να μετράει σωστά το HAL_Delay χωρίς να μπλέκει με το SysTick του FreeRTOS */
void SysTick_Handler(void);
