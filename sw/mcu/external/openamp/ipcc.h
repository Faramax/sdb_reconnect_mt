#pragma once
#include "stm32mp1xx_hal_ipcc.h"

extern IPCC_HandleTypeDef hipcc;

#ifdef __cplusplus
 extern "C" {
#endif

void MX_IPCC_Init(void);

#ifdef __cplusplus
}
#endif
