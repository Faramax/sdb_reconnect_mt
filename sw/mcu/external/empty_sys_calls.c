#include <mcu/system/error_handler.h>

#include <_syslist.h>
#include <sys/stat.h>

// For simple this functuins implementation see https://www.embecosm.com/appnotes/ean9/ean9-howto-newlib-1.0.html

int _isatty(int fd)
{
  (void) fd;
  Error_Handler();
  return -1;
}

int _write(int fd, char* ptr, int len)
{
  (void) fd;
  (void) ptr;
  (void) len;
  Error_Handler();
  return -1;
}

int _close(int fd)
{
  (void) fd;
  Error_Handler();
  return -1;
}

int _lseek(int fd, int ptr, int dir)
{
  (void) fd;
  (void) ptr;
  (void) dir;
  Error_Handler();
  return -1;
}

int _read(int fd, char* ptr, int len)
{
  (void) fd;
  (void) ptr;
  (void) len;
  Error_Handler();
  return -1;
}

int _fstat(int fd, struct stat* st)
{
  (void) fd;
  (void) st;
  Error_Handler();
  return -1;
}

void* _sbrk (int nbytes)
{
   (void) nbytes;
   Error_Handler();
   return NULL;
}

void _exit (int  rc)
{
   (void) rc;
   while(1);
}

int _kill (int  pid, int  sig)
{
   (void) pid;
   (void) sig;
   Error_Handler();
   return -1;
}

int _getpid ()
{
   Error_Handler();
   return -1;
}
