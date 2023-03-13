#include <stdlib.h>
#include <assert.h>

void __assert_func_nodetail() __attribute__((noreturn));

// most compact assert function implementation
void __assert_func_nodetail() {
   __asm volatile ("bkpt 0");
   abort();
}

// intercept standard assert functions
#define PREVENT_MACRO_SUBSTITUTION()
void __assert PREVENT_MACRO_SUBSTITUTION() (const char *p1 __unused, int p2 __unused, const char * p3 __unused) {
   __assert_func_nodetail();
}
void __assert_func PREVENT_MACRO_SUBSTITUTION() (const char *p1 __unused, int p2 __unused, const char *p3 __unused, const char *p4 __unused) {
   __assert_func_nodetail();
}

// intercept strerror
char *strerror (int errnum __unused)
{
   static char empty[1] = {0};
   return empty;
}

// intercept strerror_r
char *strerror_r (struct _reent *_r __unused, int errnum, int internal __unused, int *errptr __unused)
{
   return strerror(errnum);
}

// intercept strerror_r
char *_strerror_r (int errnum, int internal __unused, int *errptr __unused)
{
   return strerror(errnum);
}

// intercept __xpg_strerror_r
char *__xpg_strerror_r (int errnum, int internal __unused, int *errptr __unused)
{
   return strerror(errnum);
}
