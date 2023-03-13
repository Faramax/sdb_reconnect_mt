#pragma once

#include <cstdint>
#include <utility>
#include <mcu/external/openamp/rpmsg_hdr_status.h>

namespace skrm {
namespace sdb {


   struct HDR_DdrBuffTypeDef
   {
      uint32_t physAddr;
      uint32_t physSize;
   };

   class buffer_create_message_parser
   {
   public:
      static constexpr uint16_t message_size = 20;
   public:
      buffer_create_message_parser(uint8_t* buf, uint16_t size);

      std::pair<uint8_t, RPMSG_HDR_DdrBuffTypeDef> parse_next();

      bool has_message() const;

   private:
      std::pair<uint8_t, RPMSG_HDR_DdrBuffTypeDef> parse();

   private:
      uint8_t* buf_left_;
      uint16_t size_left_;
   };
}
}
