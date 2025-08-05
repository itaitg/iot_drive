//
// Created by bender on 2/20/25.
//

#include <iostream>

#include "UDP_socket.hpp"

#include <cstring>
#include <netdb.h>
#include <unistd.h>


ilrd::UDP_Socket::UDP_Socket(const char* port, const char* other_ip): Socket(port, other_ip, SOCK_DGRAM),
m_other_addr()
{

    m_other_addr = *reinterpret_cast<sockaddr_in*>(GetAddr());

    if(!other_ip)
    {
        if(bind(m_socket_fd, GetAddr() , sizeof(*GetAddr())) == -1)
        {
            throw std::runtime_error("error: bind");
        }
    }
}

ilrd::UDP_Socket::~UDP_Socket()
{

}

void ilrd::UDP_Socket::EnableBroadcast(const bool broadcast_) const
{
    const int mode = broadcast_;
    setsockopt(m_socket_fd, SOL_SOCKET, SO_BROADCAST, &mode,
        sizeof(mode));
}


size_t ilrd::UDP_Socket::Receive(std::vector<char>& buffer)
{
    socklen_t clientLen = sizeof(m_other_addr);
    ssize_t received = 0;

    received = recvfrom(m_socket_fd, buffer.data(), buffer.size(),0,
        reinterpret_cast<sockaddr*>(&m_other_addr), &clientLen);
    if(received < 0)
    {
        throw std::runtime_error("error: recvfrom");
    }

    return received;
}

void ilrd::UDP_Socket::Send(const std::vector<char>& str) const
{
    if(-1 == sendto(m_socket_fd, str.data(), str.size(), 0,
    reinterpret_cast<const sockaddr*>(&m_other_addr), sizeof(m_other_addr)))
    {
        throw std::runtime_error("error: sendto");
    }
}
