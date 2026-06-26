#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <winsock2.h>
#include <iphlpapi.h>
#include <iostream>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

void print_tcp_connection();

#endif //CONNECTION_HANDLER_H
