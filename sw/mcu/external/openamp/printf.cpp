#include "rpmsg.hpp"

extern "C"
{
   bool           g_dbg_started = false;
   skrm::rpmsg*   g_dbg_uart_ptr = nullptr;

   int vprintf ( const char * fmt, va_list ap )
   {
      int res = -1;
      if(g_dbg_uart_ptr && g_dbg_started)
      {
#ifdef SUPPORT_FORMATTED_PRINTF
         static char           s_dbg_buf[4096];
         res = vsprintf(s_dbg_buf, fmt, ap);
         if(res > 0)
            g_dbg_uart_ptr->transmit((uint8_t*)s_dbg_buf, res+1);
#else
         size_t res = strlen(fmt);
         if(res > 0)
            g_dbg_uart_ptr->transmit((uint8_t*)fmt, res+1);
#endif
      }
      return res;
   }

   int printf (const char *fmt, ...)
   {
     va_list args;
     int res;

     va_start (args, fmt);
     res = vprintf (fmt, args);
     va_end (args);
     return res;
   }

   void DBG_UART_RxCpltCallback(VIRT_UART_HandleTypeDef *huart)
   {
      g_dbg_started = true;
      printf("Msg received on VIRTUAL UART debug channel: %hu \n\r");
   }
}


void printf_init(skrm::rpmsg& uart)
{
   g_dbg_uart_ptr = &uart;
}

void wait_for_printf_ready()
{
   while(!g_dbg_started)
      skrm::rpmsg::check_for_message();
}
