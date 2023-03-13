#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include <cxxabi.h>

void __gnu_cxx::__verbose_terminate_handler()
{
   assert(false);
   std::terminate();
}

extern "C" void abi::__cxa_pure_virtual (void) {
    std::terminate();
}

extern "C" void abi::__cxa_deleted_virtual(void) {
    std::terminate();
}
