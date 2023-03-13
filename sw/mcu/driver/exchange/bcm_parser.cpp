#include "bcm_parser.hpp"
#include <cstdlib>
#include <language_extentions.hpp>

namespace skrm {
namespace sdb {

   buffer_create_message_parser::buffer_create_message_parser(uint8_t* buf, uint16_t size)
      : buf_left_(buf)
      , size_left_(size)
   {
      if(size_left_ % message_size)
      {
         // TODO: warning
         size_left_ = 0; // drop all data
      }
   }

   std::pair<uint8_t, RPMSG_HDR_DdrBuffTypeDef> buffer_create_message_parser::parse_next()
   {
      if(!has_message())
         return {};
      auto ret = parse();
      size_left_ -= message_size;
      buf_left_  += message_size;
      return ret;
   }

   bool buffer_create_message_parser::has_message() const
   {
      return size_left_;
   }

   bool hex_to_int(char c, uint8_t* return_number)
   {
      if (c >= '0' && c <= '9')
      {
         *return_number = c - '0';
         return true;
      }
      else if (c >= 'A' && c <= 'F')
      {
         *return_number = c - 'A' + 10;
         return true;
      }
      else if (c >= 'a' && c <= 'f')
      {
         *return_number = c - 'a' + 10;
         return true;
      }
      else
         return false;
   }

   bool hex_str_to_u32(uint8_t const* hex_str, uint32_t* return_number)
   {
      *return_number = 0;
      for (int i=0; i<8; i++)
      {
         uint8_t digit;
         if(!hex_to_int(hex_str[7-i], &digit))
            return false;
         *return_number |= (digit << i*4);
      }
      return true;
   }

   std::pair<uint8_t, RPMSG_HDR_DdrBuffTypeDef> buffer_create_message_parser::parse()
   {
       // example command: B0AxxxxxxxxLyyyyyyyy => Buff0 @:xx..x Length:yy..y
       if (buf_left_[0] != 'B')
       {
           // "CM4 : treatSDBEvent ERROR wrong buffer command:%c\n", buf_left_[0]);
          BREAKPOINT();
          return {};
       }

       uint8_t buf_number;
       if(!hex_to_int(buf_left_[1], &buf_number))
       {
         // "CM4 : treatSDBEvent ERROR wrong buffer index format:%c\n"
          BREAKPOINT();
          return {};
       }

       if (buf_left_[2] != 'A')
       {
            // "CM4 : treatSDBEvent ERROR wrong buffer address tag:%c instead of:A\n"
          BREAKPOINT();
          return {};
       }

      uint32_t physAddr;
      if(!hex_str_to_u32(&buf_left_[3], &physAddr))
      {
         // "CM4 : treatSDBEvent ERROR wrong address\n"
         BREAKPOINT();
         return {};
      }

      if (buf_left_[11] != 'L')
      {
         // "CM4 : treatSDBEvent ERROR wrong buffer length tag:%c instead of:L\n"
         BREAKPOINT();
         return {};
      }

      uint32_t physSize;
      if(!hex_str_to_u32(&buf_left_[12], &physSize))
      {
         // "CM4 : treatSDBEvent ERROR wrong length\n"
         BREAKPOINT();
         return {};
      }

      return {buf_number, {physAddr, physSize}};
   }

}
}
