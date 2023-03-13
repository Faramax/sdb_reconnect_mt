#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include <sys/time.h>

#include <stm32_hal.h>

#undef errno
extern int errno;

char *__env[1] = { 0 };
char **environ = __env;

int _write(int file, char *ptr, int len);

void _exit(int __status)
{
   if (CoreDebug->DHCSR & 1)
   {
      __BKPT(0);
      while(1) { };
   }
   NVIC_SystemReset();
}


int _close(int file)
{
    return -1;
}

int _execve(char *name, char **argv, char **env)
{
    errno = ENOMEM;
    return -1;
}

int _fork()
{
    errno = EAGAIN;
    return -1;
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _getpid()
{
    return 1;
}

int _gettimeofday(struct timeval *tv, struct timezone *tz)
{
    tv->tv_sec = HAL_GetTick() / 1000000;
    tv->tv_usec = HAL_GetTick() % 1000000;
    return 0;
}

int _isatty(int file)
{
    switch (file)
    {
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return 0;
    }
}

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return (-1);
}

int _link(char *old, char *new)
{
    errno = EMLINK;
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

caddr_t _sbrk(int incr)
{
    extern char _ebss;
    extern char _Min_Heap_Size;
    static char *heap_end = &_ebss;
    char *prev_heap_end;

    prev_heap_end = heap_end;

    if(prev_heap_end + incr > &_ebss + (unsigned)&_Min_Heap_Size)
    {
       __asm volatile ("bkpt 0");
        _write(STDERR_FILENO, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        return (caddr_t) - 1;
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

int _read(int file, char *ptr, int len)
{
    errno = EBADF;
    return -1;

}

int _stat(const char *filepath, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

clock_t _times(struct tms *buf)
{
    return -1;
}

int _unlink(char *name)
{
    errno = ENOENT;
    return -1;
}

int _wait(int *status)
{
    errno = ECHILD;
    return -1;
}

int _write(int file, char *ptr, int len)
{
    return -1;
}
