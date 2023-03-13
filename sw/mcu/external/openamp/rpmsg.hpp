#pragma once
#include "openamp.h"

// C++ wrap on the openamp rpmsg

namespace skrm {

   void openamp_init();

   class rpmsg
   {
   public:
      using callback_fn_type = void (*)(VIRT_UART_HandleTypeDef *huart);

      void                    init(callback_fn_type rx_callback_fn);
      VIRT_UART_StatusTypeDef transmit(uint8_t* buf, uint16_t size);

   //! This function handles messages for all rpmsg instances.
   //! If you want to handle messages for only one rpmsg instance, you should
   //! rework openamp.c and make rpmsg_virtio_device rvdev as this class member
      static void check_for_message();

   private:
      VIRT_UART_HandleTypeDef huart_;
   };

}
