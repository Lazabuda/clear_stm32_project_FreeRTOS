#include "main.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

// Program delay function
void Soft_Delay(volatile uint32_t number)
{
  while(number--);
}

void blink(void *pvParameters)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef  ledinit;  // To create a structure

  ledinit.GPIO_Mode = GPIO_Mode_OUT;  // Mode - output
  ledinit.GPIO_OType = GPIO_OType_PP;  // Type - Push Pull
  ledinit.GPIO_PuPd = GPIO_PuPd_NOPULL;  // Without pullup/pulldown
  ledinit.GPIO_Speed = GPIO_Speed_2MHz;  // Speed 2 MHz
  ledinit.GPIO_Pin = GPIO_Pin_13; // The number of pin - 13

  GPIO_Init(GPIOC, &ledinit);
  while(1)
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    Soft_Delay(0x00FFFFFF);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    Soft_Delay(0x00FFFFFF);
  }
}

int main (void) 
{
  xTaskCreate(blink, "Blink", 128, NULL, 2, NULL);
  vTaskStartScheduler();
  while(1) 
  {
    
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

void vApplicationTickHook()
{

}

void vApplicationStackOverflowHook(TaskHandle_t handle, char *name) {
(void)handle;
	for (;;){}
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
  
}
#endif /* USE_FULL_ASSERT */

