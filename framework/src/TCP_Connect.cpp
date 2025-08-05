//
// Created by bender on 2/23/25.
//

#include "TCP_Connect.hpp"

#include <cstring>

ilrd::TCP_Connect::TCP_Connect(const char* port, const char* other_ip): Socket
(port, other_ip, SOCK_STREAM)
{
    if(-1 == connect(m_socket_fd, GetAddr(), sizeof(*GetAddr())))
    {
        throw std::runtime_error("error: connect");
    }
#ifndef NDEBUG
    std::cout << "TCP: Connection made..." << std::endl;
#endif
}

ilrd::TCP_Connect::TCP_Connect(int fd): Socket(fd)
{}

ilrd::TCP_Connect::~TCP_Connect()
{
#ifndef NDEBUG
    std::cout << "TCP: Disconnected..." << std::endl;
#endif
}

size_t ilrd::TCP_Connect::Receive(std::vector<char>& buffer)
{
    size_t size_of_message = 0;
    while(size_of_message < buffer.size())
    {
        size_of_message += recv(m_socket_fd, buffer.data() + size_of_message, buffer.size() - size_of_message, 0);
    }

    return  size_of_message;
}

void ilrd::TCP_Connect::Send(const std::vector<char>& buffer) const
{
    size_t size_of_message = 0;
    while(size_of_message < buffer.size())
    {
        size_of_message += send(m_socket_fd, buffer.data() + size_of_message, buffer.size() - size_of_message, MSG_NOSIGNAL);
    }
}