#include "error_handler.h"
#include <stdlib.h>

void Error_Handler(void)
{
//  log_err("Error_Handler");
//  HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
  __asm volatile ("bkpt 0");
  exit(1);
}
