#pragma once

#ifdef CORE_CM4
   #define BREAKPOINT() __asm volatile ("bkpt 0");
#else
   #define BREAKPOINT()
#endif

#define sce static constexpr

namespace skrm{
   struct unmovable
   {
      unmovable() = default;
      unmovable(unmovable&&) = delete;
      unmovable& operator=(unmovable&&) = delete;
   };

   struct uncopyable
   {
      uncopyable() = default;
      uncopyable(uncopyable const&) = delete;
      uncopyable& operator=(uncopyable const&) = delete;
   };

   struct fixed : public uncopyable, public unmovable
   {};
}
