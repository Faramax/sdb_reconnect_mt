#include "buffer_ctrl.hpp"
#include <cstddef>
#include <tuple>
#include <cstring>
#include <cassert>
#include <mcu/driver/general/error_handler.h>
#include <language_extentions.hpp>

namespace skrm {
namespace sdb {

   bool buffer_ctrl::ready() const
   {
      return ddr_buff_count_ == max_ddr_buff;
   }

   uint8_t buffer_ctrl::current_buf() const
   {
      return sh_.buff_index;
   }

   bool buffer_ctrl::add_to_send(void const* data, size_t size)
   {
      assert(ready());
      size_t const free_area_size = ddr_buff_array_[sh_.buff_index].physSize - sh_.filled_size;
      if(size > free_area_size)
         return false;
      uint8_t* free_area_begin = (uint8_t*)((size_t)ddr_buff_array_[sh_.buff_index].physAddr) + sh_.filled_size;
      memcpy(free_area_begin, data, size);
      sh_.filled_size += size;
      return true;
   }

   std::pair<void *, size_t> buffer_ctrl::get_free_area() const
   {
      assert(ready());
      size_t const free_area_size = ddr_buff_array_[sh_.buff_index].physSize - sh_.filled_size;
      uint32_t const phys_addr = ddr_buff_array_[sh_.buff_index].physAddr;
      uint8_t* free_area_begin = (uint8_t*)((size_t)phys_addr) + sh_.filled_size;
      return {free_area_begin, free_area_size};
   }

   void buffer_ctrl::filled(size_t size)
   {
      size_t const free_area_size = ddr_buff_array_[sh_.buff_index].physSize - sh_.filled_size;
      assert(size <= free_area_size);
      (void)free_area_size;   // TODO : change assert ->assertlog
      sh_.filled_size += size;
   }

   buffer_ctrl::snapshot buffer_ctrl::make_snapshot(bool may_change)
   {
      assert(ready());
      snapshot const sh = sh_;
      if(may_change)
         sh_.buff_index = (sh_.buff_index + 1)%max_ddr_buff;
      sh_.filled_size = 0;
      return sh;
   }

   void buffer_ctrl::add_new_buffer(const std::pair<uint8_t, RPMSG_HDR_DdrBuffTypeDef> &buf)
   {
      uint8_t                    buf_number;
      RPMSG_HDR_DdrBuffTypeDef   buf_hdr;
      std::tie(buf_number, buf_hdr) = buf;

      if((buf_number >= max_ddr_buff) || (buf_number > ddr_buff_count_))
      {
         BREAKPOINT();
         // "CM4 : treatSDBEvent ERROR wrong buffer received index:%c maximum index:%d\n" buf_number, max_ddr_buff);
         return;
      }
      else if(buf_number == ddr_buff_count_) // new buffer
      {
         ddr_buff_array_[buf_number] = buf_hdr;
         ddr_buff_count_++;
      }
      else if(    // rewriting current buf params. here (buf_number < ddr_buff_count_)
         (ddr_buff_array_[buf_number].physAddr != buf_hdr.physAddr) ||
         (ddr_buff_array_[buf_number].physSize != buf_hdr.physSize)
      )
      {
         BREAKPOINT();
         // warning message
         ddr_buff_array_[buf_number] = buf_hdr;
      }
      else
      {
//         BREAKPOINT();
         // warning message
      }
   }

   void buffer_ctrl::reset()
   {
      for(int i = 0; i < ddr_buff_count_; ++i)
      {
         ddr_buff_array_[i].physSize = 0;
         ddr_buff_array_[i].physAddr = 0;
      }
      sh_.buff_index = 0;
      sh_.filled_size = 0;
      ddr_buff_count_ = 0;
   }

}
}
