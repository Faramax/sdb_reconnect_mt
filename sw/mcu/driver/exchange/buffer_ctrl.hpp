#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <utility>
#include <mcu/external/openamp/rpmsg_hdr_status.h>

namespace skrm {
namespace sdb {

/* SKRM M5 proto specific sdb exchange. Strongly 3 fixed size buffers. Wite to them one by one.*/
   class buffer_ctrl
   {
   public:
      struct snapshot
      {
         uint8_t  buff_index;
         uint32_t filled_size;
      };

      bool     ready() const;
      uint8_t  current_buf() const;

   // Copy your data to send buffer. Call only if ready().
      bool     add_to_send(const void *, size_t);

   // Get free part of the current output buffer to fill it by yourself. Call only if ready().
      std::pair<void*, size_t>   get_free_area() const;

   // Inform class that you've filled size bytes in the output buffer. Call only if ready().
      void     filled(size_t);

   // Makes snapshot and switches on the next buffer. Call only if ready().
      snapshot make_snapshot(bool may_change);

   // interface that will be called from sdb hardware
   public:
      void add_new_buffer(const std::pair<uint8_t, RPMSG_HDR_DdrBuffTypeDef> &buf);
      void reset();

   public:
      static constexpr size_t max_ddr_buff = 3;

   private:
      using ddr_buf_array = std::array<RPMSG_HDR_DdrBuffTypeDef, max_ddr_buff>;
      ddr_buf_array           ddr_buff_array_{};        // used to store DDR buff allocated by Linux driver
      uint8_t                 ddr_buff_count_ = 0;
      snapshot                sh_ = {};
   };
}
}
