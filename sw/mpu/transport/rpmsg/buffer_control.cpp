/**
 * remote processor messaging (rpmsg) with shared data buffers (sdb)
 */

#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/eventfd.h>
#include <termios.h>
#include <logger/logger.h>
#include "buffer_control.hpp"

namespace utc {
namespace transport {
namespace rpmsg {

shared_buffer::shared_buffer(size_t sz, int fd)
   :  capacity(sz)
{
   data = mmap(0, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
   RELAY_LOG_TRACE(skrm::p7_modules::system, "Mmap %d bytes into 0x%p", sz, data)
   if (data == MAP_FAILED)
      RELAY_LOG_ERROR(skrm::p7_modules::system, "Mmap failed: %s", std::strerror(errno))
}

shared_buffer::~shared_buffer()
{
   if (data != nullptr && capacity != 0 && munmap(data, capacity) < 0)  {
      RELAY_LOG_ERROR(skrm::p7_modules::system, "Munmap failed: %s", std::strerror(errno))
   }
   RELAY_LOG_TRACE(skrm::p7_modules::system, "Munmap %d bytes from 0x%p", capacity, data)
}

int driver_event::event_count = 0;

driver_event::driver_event(int fd, pollfd &request)
   : poll_request(request)
{
   // event notification from driver
   int ev = eventfd(0,0);
   if (ev < 0) {
      RELAY_LOG_ERROR(skrm::p7_modules::system, "Create eventfd failed: %s", std::strerror(errno))
      return;
   }

   // kernel driver ignores buffer ID and sets it incrementally
   event_for_driver event{0, ev};
   if (ioctl(fd, _IOW('R', 0x00, struct event_for_driver *), &event) < 0) {
         RELAY_LOG_ERROR(skrm::p7_modules::system, "Ioctl for setting event failed: %s", std::strerror(errno))
         return;
   }

   // kernel driver increments buffer ID on each ioctl call, we set event_idx to kernel buffer ID
   event_idx = event_count++;
   poll_request.fd = ev;
   poll_request.events = POLLIN;
   RELAY_LOG_TRACE(skrm::p7_modules::system, "Event #%d with fd %d created", event_idx, ev)
}

driver_event::~driver_event()
{
   if(poll_request.fd < 0)
      return;

   int const ec = close(poll_request.fd);
   if (ec < 0)
      RELAY_LOG_ERROR(skrm::p7_modules::system, "Close eventfd #%d failed: %s", poll_request.fd, std::strerror(errno))
   else
      RELAY_LOG_TRACE(skrm::p7_modules::system, "Eventfd #%d closed", poll_request.fd)
}

size_t buffer_control::buffer_size() const
{
   size_from_driver size{buffer_id(), 0};
   if (ioctl(devfd, _IOWR('R', 0x01, struct size_from_driver *), &size) < 0)
         RELAY_LOG_ERROR(skrm::p7_modules::system, "Ioctl for getting buffer size failed: %s", std::strerror(errno))

   RELAY_LOG_TRACE(skrm::p7_modules::system, "Driver reports %u bytes in buffer #%d", size.buffer_size, size.buffer_id)
   return size.buffer_size;
}

bool buffer_control::buffer_ready() const
{
   bool ready = event().revents & POLLIN;
   RELAY_LOG_TRACE(skrm::p7_modules::system, "Buffer #%d ready status %d", buffer_id(), ready)
   return ready;
}

bool buffer_control::buffer_error() const
{
   short int const re = event().revents;
   return (re & POLLERR) || (re & POLLHUP) || (re & POLLNVAL);
}

bool buffer_control::clear_status() const
{
   uint64_t event_counter {};
   // clear ready status for next polling
   if (read(event().fd, &event_counter, sizeof(event_counter)) < 0)
      RELAY_LOG_ERROR(skrm::p7_modules::system, "Clear eventfd failed: %s", std::strerror(errno))
   else if (event_counter != 1)
      RELAY_LOG_WARNING(skrm::p7_modules::system, "Illegal event counter: %lld, possible buffer corruption", event_counter)
   else
      RELAY_LOG_TRACE(skrm::p7_modules::system, "Eventfd cleared")

   return event_counter == 1;
}

}
}
}
