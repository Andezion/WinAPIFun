#include "connection_handler.h"

std::string ip_to_string(DWORD ip)
{
    in_addr addr;
    addr.s_addr = ip;

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr, str, sizeof(str));
    return std::string(str);
}

void print_tcp_connection()
{
    PMIB_TCPTABLE_OWNER_PID tcp_table{};
    DWORD dw_size = 0;

    DWORD dw_result = GetExtendedTcpTable(NULL, &dw_size, true, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
    if (dw_result != ERROR_INSUFFICIENT_BUFFER)
    {
        std::cerr << "GetExtendedTcpTable error: " << dw_result << std::endl;
    }

    tcp_table = (PMIB_TCPTABLE_OWNER_PID) malloc(dw_size);
    dw_result = GetExtendedTcpTable(tcp_table, &dw_size, true, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
    if (dw_result != NO_ERROR)
    {
        std::cout << "Active connection: " << tcp_table->dwNumEntries << std::endl;

        for (DWORD i = 0; i < tcp_table->dwNumEntries; i++)
        {
            in_addr local_addr{}, remote_addr{};

            local_addr.S_un.S_addr = tcp_table->table[i].dwLocalAddr;
            remote_addr.S_un.S_addr = tcp_table->table[i].dwRemoteAddr;

            printf("Local IP: %s:%d | Remote IP: %s:%d | PID: %d\n",
                inet_ntoa(local_addr), ntohs(static_cast<u_short>(tcp_table->table[i].dwLocalPort)),
                inet_ntoa(remote_addr), ntohs(static_cast<u_short>(tcp_table->table[i].dwRemotePort)),
                tcp_table->table[i].dwOwningPid);
        }
    } else
    {
        std::cout << "Error in connection table";
    }

    free(tcp_table);
}

// int main() {
//     WSADATA wsaData;
//     if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//         std::cerr << "WSAStartup failed." << std::endl;
//         return 1;
//     }
//
//     ULONG size = 0;
//     GetExtendedTcpTable(nullptr, &size, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
//
//     PMIB_TCPTABLE_OWNER_PID pTcpTable = (PMIB_TCPTABLE_OWNER_PID)malloc(size);
//
//     if (GetExtendedTcpTable(pTcpTable, &size, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) == NO_ERROR) {
//         std::cout << "Local Address\tLocal Port\tRemote Address\tRemote Port\tPID\n";
//         std::cout << "-------------------------------------------------------------------\n";
//
//         for (DWORD i = 0; i < pTcpTable->dwNumEntries; i++) {
//             MIB_TCPROW_OWNER_PID row = pTcpTable->table[i];
//             std::cout << ip_to_string(row.dwLocalAddr) << "\t"
//                       << ntohs((WORD)row.dwLocalPort) << "\t\t"
//                       << ip_to_string(row.dwRemoteAddr) << "\t"
//                       << ntohs((WORD)row.dwRemotePort) << "\t\t"
//                       << row.dwOwningPid << "\n";
//         }
//     } else {
//         std::cerr << "Failed to get TCP table." << std::endl;
//     }
//
//     free(pTcpTable);
//     WSACleanup();
//     return 0;
// }