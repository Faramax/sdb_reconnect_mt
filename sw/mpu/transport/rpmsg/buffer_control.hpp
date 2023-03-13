/**
 * remote processor messaging (rpmsg) with shared data buffers (sdb)
 */

#pragma once
#include <vector>
#include <cstdint>
#include <sys/poll.h>
#include <language_extentions.hpp>

namespace utc {
namespace transport {
namespace rpmsg {

/**
 * @brief Mapping memory handled by file desciptor fd
 * fd might be /dev/rpmsg-sdb, /dev/uio, /dev/mem
 * or any other descriptor capable for mapping
 */
struct shared_buffer : public skrm::uncopyable
{
   shared_buffer() = default;
   shared_buffer(size_t sz, int fd);
   ~shared_buffer();

   size_t   capacity {};
   void *   data {};
};

/**
 * @brief Event notification from rpmsg-sdb driver
 * MCU informs rpmsg-sdb driver when data is ready via rpmsg,
 * rpmsg-sdb driver informs userspace via event notification
 */
struct driver_event {
   driver_event(int fd /* /dev/rpmsg-sdb file desciptor */, pollfd &);
   ~driver_event();

   struct event_for_driver {
      int bufferid, eventfd;
   } ;

   static int     event_count;
   int            event_idx {};
   pollfd         &poll_request;
};

/**
 * @brief Memory-mapped buffer control for M4->A7 buffers
 * via rpmsg-sdb driver
 */
class buffer_control {
public:
   //! params:
   //!  * fd /dev/rpmsg-sdb file desciptor
   buffer_control(size_t sz, int fd, pollfd &pfd)
      : incoming_event(fd, pfd)
      , incoming_buffer(sz, fd)
      , devfd(fd)
   {}

   struct size_from_driver {
      int      buffer_id;
      uint32_t buffer_size;
   };

   pollfd   event() const { return incoming_event.poll_request; }
   int      buffer_id() const { return incoming_event.event_idx; }
   void *   buffer_data() const { return incoming_buffer.data; }

   size_t   buffer_size() const;
   bool     buffer_ready() const;
   bool     buffer_error() const;
   bool     clear_status() const;

private:
   // driver event must be constructed BEFORE
   // buffer itself for proper driver initialization
   driver_event   incoming_event;
   shared_buffer  incoming_buffer;
   int            devfd {};
};

}
}
}
