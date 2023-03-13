//
// Created by sergey on 3/2/23.
//

#include "send_data.h"

#include <cstdint>
#include <tuple>

#include <mcu/driver/general/error_handler.h>

#include <mcu/external/openamp/rpmsg.hpp>
#include <mcu/driver/exchange/buffer_ctrl.hpp>
#include <mcu/external/openamp/rpmsg_hdr.h>

extern uint32_t                  base_of_transmit;

using namespace                  skrm;
using namespace                  skrm::sdb;

extern buffer_ctrl               g_buffers;
extern uint8_t                   g_rpmsg_buffer[1024 * 4];

extern RPMSG_HDR_HandleTypeDef   hsdb0;
extern rpmsg                     huart0;
extern rpmsg                     huart1;

void send_data_rpmsg(uint32_t size_to_transmit)
{
   volatile uint32_t* ddr_it = (uint32_t*)g_rpmsg_buffer;
   for(uint32_t i = 0; i < size_to_transmit; ++i)
   {
      *ddr_it = base_of_transmit + i;
      ++ddr_it;
   }
   ++base_of_transmit;

   uint8_t* it = g_rpmsg_buffer;
   while(size_to_transmit)
   {
      uint32_t const max_chunk = (RPMSG_BUFFER_SIZE-16);
      uint32_t chunk_to_transmit = (size_to_transmit > max_chunk) ? max_chunk : size_to_transmit;
      huart1.transmit(it, chunk_to_transmit);
      size_to_transmit -= chunk_to_transmit;
      it += chunk_to_transmit;
   }
}

void send_data_sdb(uint32_t size_to_transmit)
{
   if(!g_buffers.ready())
      return;

   uint32_t   buf_free_area;
   void*      buf_begin_ptr;
   std::tie(buf_begin_ptr, buf_free_area) = g_buffers.get_free_area();

   if(size_to_transmit > buf_free_area)
      Error_Handler();
   volatile uint32_t* ddr_it = (uint32_t*)buf_begin_ptr;
   for(uint32_t i = 0; i < size_to_transmit; ++i)
   {
      *ddr_it = base_of_transmit + i;
      ++ddr_it;
   }
   ++base_of_transmit;

   std::atomic_thread_fence(std::memory_order_acq_rel);

   g_buffers.filled(size_to_transmit);

   buffer_ctrl::snapshot const sh = g_buffers.make_snapshot(false);

   char mSdbBuffTx[20];
   sprintf(mSdbBuffTx, "B%dL%08x", sh.buff_index, sh.filled_size);
   if(RPMSG_HDR_StatusTypeDef::RPMSG_HDR_OK != RPMSG_HDR_Transmit(&hsdb0, (uint8_t*)mSdbBuffTx, strlen(mSdbBuffTx)))
   {
      Error_Handler();
   }
}

void send_data(uint32_t const size_to_transmit)
{
//   send_data_rpmsg(size_to_transmit);
   send_data_sdb(size_to_transmit);
}
