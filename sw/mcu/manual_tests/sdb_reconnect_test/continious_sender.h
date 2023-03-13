//
// Created by sergey on 3/2/23.
//

#ifndef UTC_CONTINIOUS_SENDER_H
#define UTC_CONTINIOUS_SENDER_H

#include <atomic>
#include "stm32mp1xx_hal.h"
#include "send_data.h"

class continious_sender {
public:
   void start(uint32_t send_period_ms, uint32_t size)
   {
      send_period_ = send_period_ms;
      size_ = size;
      started_.store(true);
      last_send_time_ = HAL_GetTick();
   }

   void stop()
   {
      started_.store(false);
   }

   void check_out()
   {
      auto const cur_time = HAL_GetTick();
      if(cur_time - last_send_time_ > send_period_)
      {
         send_data_sdb(size_);
         last_send_time_ = cur_time;
      }
   }

private:
   std::atomic_bool        started_;
   std::atomic<uint32_t>   last_send_time_;
   std::atomic<uint32_t>   send_period_;
   std::atomic<uint32_t>   size_;
};


#endif //UTC_CONTINIOUS_SENDER_H
