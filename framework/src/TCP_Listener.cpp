//
// Created by bender on 2/22/25.
//

#include "TCP_Listener.hpp"

#include <unistd.h>

ilrd::TCP_Listener::TCP_Listener(const char* port): Socket
(port, NULL, SOCK_STREAM)
{
    int y = 1;

    if(setsockopt(m_socket_fd, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int)) == -1)
    {
        throw std::runtime_error("error: setsockopt");
    }
    if(-1 == bind(m_socket_fd, GetAddr(), sizeof(*GetAddr())))
    {
        throw std::runtime_error("error: bind");
    }
    if(-1 == listen(m_socket_fd, 10))
    {
        throw std::runtime_error("error: listen");
    }
#ifndef NDEBUG
    std::cout << "TCP Listener: operating..." << std::endl;
#endif
}
ilrd::TCP_Listener::~TCP_Listener()
{
#ifndef NDEBUG
    std::cout << "TCP Listener: Closed..." << std::endl;
#endif
}


ilrd::TCP_Connect* ilrd::TCP_Listener::Connect() const
{
    int connection_fd = accept(m_socket_fd, NULL,NULL);
#ifndef NDEBUG
    std::cout << "TCP Listener: Made connection..." << std::endl;
#endif
    return new TCP_Connect(connection_fd);
}

void ilrd::TCP_Listener::Disconnect(const TCP_Connect* connection)
{
#ifndef NDEBUG
    std::cout << "TCP Listener: Disconnected with client..." << std::endl;
#endif
    delete connection;
}

size_t ilrd::TCP_Listener::Receive(std::vector<char>& buffer)
{
    (void)&buffer;
    return 0;
}

void ilrd::TCP_Listener::Send(const std::vector<char>& str) const
{
    (void)str;
}


