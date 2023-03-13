#include <iostream>
#include <atomic>
#include <thread>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>

#include <signal.h>

#include <logger/logger.h>
#include <mpu/transport/rpmsg/buffer_control.hpp>

std::atomic_bool              task_enabled(true);
void ctrlc_handler(int /*unused*/)
{
   task_enabled = false;
}

int                           device_fd;
std::string                   device_path = "/dev/rpmsg-sdb";

size_t const                  number_of_buffers = 3;
size_t const                  buffer_size = 32*1024;

std::vector<pollfd>           events_;
using utc::transport::rpmsg::buffer_control;
using                         buffer_control_ptr = std::unique_ptr<buffer_control>;
std::vector<buffer_control_ptr>   buffers_;

void sdb_init();

void sdb_open()
{
   device_fd = ::open(device_path.c_str(), O_RDWR |  O_NOCTTY | O_NONBLOCK);
   if (device_fd < 0)
   {
      RELAY_LOG_ERROR(skrm::p7_modules::system, "Open %s failed: %s", device_path.c_str(), std::strerror(errno))
      throw std::runtime_error("Open failed: " + device_path);
   }
   else
   {
      RELAY_LOG_INFO(skrm::p7_modules::system, "%s opened", device_path.c_str())
      sdb_init();
   }
}

void sdb_init()
{
   buffers_.clear();
   events_.clear();
   for (size_t n = 0; n < number_of_buffers; n++)
   {
      events_.emplace_back(pollfd{});
      buffers_.emplace_back(std::make_unique<buffer_control>(buffer_size, device_fd, events_.back()));
   }
   RELAY_LOG_INFO(skrm::p7_modules::system, "%s inited", device_path.c_str())
}

void sdb_close()
{
   if (device_fd < 0)
      return;

   if (::close(device_fd))
   {
      RELAY_LOG_ERROR(skrm::p7_modules::system, "Close failed: %s", std::strerror(errno))
      throw std::runtime_error("Close failed: " + device_path);
   }
   else
   {
      device_fd = -1;
      RELAY_LOG_INFO(skrm::p7_modules::system, "%s closed", device_path.c_str())
   }
}

int main()
{
   using namespace skrm;
   using namespace utc::transport::rpmsg;

   signal(SIGINT, ctrlc_handler);
   signal(SIGTERM, ctrlc_handler);

   std::chrono::milliseconds  timeout(500);
   int                        n = 0;

   try {
      while (task_enabled)
      {
         std::this_thread::sleep_for(timeout);

         {
            std::cout << "receiver close... " << std::flush;
            RELAY_LOG_TRACE(skrm::p7_modules::system, "receiver close...")
            sdb_close();
            std::cout << "done.\n" << std::endl << std::flush;
            RELAY_LOG_TRACE(skrm::p7_modules::system, "receiver close finished")
         }

         std::this_thread::sleep_for(timeout);

         {
            std::cout << "receiver.open... " << std::flush;
            RELAY_LOG_TRACE(skrm::p7_modules::system, "receiver open...")
            sdb_open();
            std::cout << "done. N = " << n++ << std::endl << std::flush;
            RELAY_LOG_TRACE(skrm::p7_modules::system, "receiver open finished")
         }
      }
   }
   catch(const std::exception &error) {
      std::cout << error.what() << std::endl << std::flush;
      return EXIT_FAILURE;
   }
   return 0;
}
