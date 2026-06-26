#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

void print_tcp_connection();

#endif //CONNECTION_HANDLER_H
