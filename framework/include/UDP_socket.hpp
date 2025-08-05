//
// Created by bender on 2/20/25.
//

#include <vector>
#include <netinet/in.h>

#include "Socket.hpp"


#ifndef ILRD_RD329_UDP_SOCKET_HPP
#define ILRD_RD329_UDP_SOCKET_HPP

namespace ilrd
{
    class UDP_Socket : public Socket
    {
    public:
        UDP_Socket(const char* port, const char* other_ip = NULL);
        ~UDP_Socket();

        void EnableBroadcast(bool broadcast_) const;

        size_t Receive(std::vector<char>& buffer);
        void Send(const std::vector<char>& str) const;

    private:

        sockaddr_in m_other_addr;
    };
}
#endif //ILRD_RD329_UDP_SOCKET_HPP
