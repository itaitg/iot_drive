//
// Created by bender on 2/22/25.
//


#include <netdb.h>
#include <iostream>
#include <unistd.h>

#include "Socket.hpp"



ilrd::Socket::Socket(const char* port, const char* ip, int type): m_socket_fd()
{
    addrinfo hints = {};
    int status = 0;
    hints.ai_family = AF_INET;
    hints.ai_socktype = type;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(ip, port, &hints, &res);
    if(status)
    {
        std::cout << gai_strerror(status) << std::endl;
        throw std::runtime_error("error: getaddrinfo");
    }
    m_socket_fd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if(m_socket_fd == -1)
    {
        throw std::runtime_error("error: socket");
    }
}

ilrd::Socket::Socket(int fd): m_socket_fd(fd), res()
{}

ilrd::Socket::~Socket()
{
    freeaddrinfo(res);
    close(m_socket_fd);
}

int ilrd::Socket::Getfd() const
{
    return m_socket_fd;
}

struct sockaddr* ilrd::Socket::GetAddr() const
{
    return res->ai_addr;
}

