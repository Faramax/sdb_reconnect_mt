#include "rpmsg.hpp"

#include "stm32mp1xx_hal_rcc.h"
#include "virt_uart.h"
#include "ipcc.h"
#include "openamp/rpmsg_virtio.h"
#include <mcu/driver/general/error_handler.h>

namespace skrm {

   void openamp_init()
   {
      __HAL_RCC_HSEM_CLK_ENABLE();
      MX_IPCC_Init();
      MX_OPENAMP_Init(RPMSG_REMOTE, NULL);
   }

   void rpmsg::init(callback_fn_type rx_callback_fn)
   {
      if (VIRT_UART_Init(&huart_) != VIRT_UART_OK) {
         //        log_err("VIRT_UART_Init UART0 failed.\r\n");
         Error_Handler();
      }
      if(VIRT_UART_RegisterCallback(&huart_, VIRT_UART_RXCPLT_CB_ID, rx_callback_fn) != VIRT_UART_OK)
      {
        Error_Handler();
      }
   }

   VIRT_UART_StatusTypeDef rpmsg::transmit(uint8_t *buf, uint16_t size)
   {
      return VIRT_UART_Transmit(&huart_, buf, size);
   }

   void rpmsg::check_for_message()
   {
      OPENAMP_check_for_message();
   }
}
