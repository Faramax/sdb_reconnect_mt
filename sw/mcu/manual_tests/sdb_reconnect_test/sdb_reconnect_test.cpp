#include <cstring>

#include <mcu/driver/general/error_handler.h>
#include <mcu/external/openamp/ipcc.h>

#include "stm32mp1xx_hal.h"
#include "stm32mp1xx_hal_ipcc.h"

#include <openamp.h>

#include <mcu/external/openamp/rpmsg.hpp>

#include <mcu/driver/exchange/buffer_ctrl.hpp>
#include <mcu/driver/exchange/bcm_parser.hpp>

#include "rpmsg_hdr.h"

void CoproSync_ShutdownCb(IPCC_HandleTypeDef * hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);

/* Private typedef -----------------------------------------------------------*/
#define COPRO_SYNC_SHUTDOWN_CHANNEL  IPCC_CHANNEL_3

/* Private variables ---------------------------------------------------------*/
RPMSG_HDR_HandleTypeDef hsdb0;

using namespace         skrm;
using namespace         skrm::sdb;
buffer_ctrl             g_buffers;

void buffer_create_callback(RPMSG_HDR_HandleTypeDef *huart)
{
   buffer_create_message_parser parser(huart->pRxBuffPtr, huart->RxXferSize);
   while(parser.has_message())
   {
      g_buffers.add_new_buffer(parser.parse_next());
   }
}

int main(void)
{
   using namespace skrm;

   HAL_Init();

   if(IS_ENGINEERING_BOOT_MODE())
      exit(1);

   openamp_init();

   HAL_IPCC_ActivateNotification(&hipcc, COPRO_SYNC_SHUTDOWN_CHANNEL, IPCC_CHANNEL_DIR_RX, CoproSync_ShutdownCb);

   if (RPMSG_HDR_Init(&hsdb0) != RPMSG_HDR_StatusTypeDef::RPMSG_HDR_OK)
   {
     Error_Handler();
   }
   if(RPMSG_HDR_RegisterCallback(&hsdb0, RPMSG_HDR_RXCPLT_CB_ID, buffer_create_callback) != RPMSG_HDR_StatusTypeDef::RPMSG_HDR_OK)
   {
     Error_Handler();
   }

   while (1)
   {
      OPENAMP_check_for_message();
   }

   return 0;
}

void CoproSync_ShutdownCb(IPCC_HandleTypeDef * hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir __attribute__((unused)))
{
   HAL_IPCC_NotifyCPU(hipcc, ChannelIndex, IPCC_CHANNEL_DIR_RX);
}
