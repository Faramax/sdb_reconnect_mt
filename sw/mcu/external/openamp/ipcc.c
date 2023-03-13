#include "ipcc.h"
#include <mcu/driver/general/error_handler.h>

IPCC_HandleTypeDef hipcc;

void MX_IPCC_Init(void)
{
  hipcc.Instance = IPCC;
  if (HAL_IPCC_Init(&hipcc) != HAL_OK)
  {
     Error_Handler();
  }
}
