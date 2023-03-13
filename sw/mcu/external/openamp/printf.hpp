#pragma once

extern "C"
{
   void DBG_UART_RxCpltCallback(VIRT_UART_HandleTypeDef *huart);
}

void printf_init(skrm::rpmsg& uart);

// RPMSG starts transmit only after the first receive
void wait_for_printf_ready();
