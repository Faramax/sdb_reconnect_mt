//
// Created by sergey on 3/2/23.
//

#ifndef UTC_SEND_DATA_H
#define UTC_SEND_DATA_H

#include <cstdint>

void send_data_rpmsg(uint32_t size_to_transmit);

void send_data_sdb(uint32_t size_to_transmit);

void send_data(uint32_t size_to_transmit);

#endif //UTC_SEND_DATA_H
