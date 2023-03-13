#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

   typedef struct __RPMSG_HDR_DdrBuffTypeDef
   {
     size_t physAddr;
     size_t physSize;
   }RPMSG_HDR_DdrBuffTypeDef;

#ifdef __cplusplus
}
#endif

#ifndef __cplusplus
typedef enum
{
    RPMSG_HDR_OK       = 0x00U,
    RPMSG_HDR_ERROR    = 0x01U,
    RPMSG_HDR_BUSY     = 0x02U,
    RPMSG_HDR_TIMEOUT  = 0x03U
} RPMSG_HDR_StatusTypeDef;
#else
// Equal analog of the RPMSG_HDR_StatusTypeDef. We need duplicate it for
// accurate hash calculation. Our hash calculation function can't work with
// C enums.

#pragma pack(push)
#pragma pack(4)
   enum class RPMSG_HDR_StatusTypeDef : uint32_t
   {
      RPMSG_HDR_OK       = 0x00U,
      RPMSG_HDR_ERROR    = 0x01U,
      RPMSG_HDR_BUSY     = 0x02U,
      RPMSG_HDR_TIMEOUT  = 0x03U
   };
#pragma pack(pop)
#endif
