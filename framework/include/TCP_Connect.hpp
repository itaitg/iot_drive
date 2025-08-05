//
// Created by bender on 2/23/25.
//

#ifndef ILRD_RD329_TCP_CONNECT_HPP
#define ILRD_RD329_TCP_CONNECT_HPP

#include <iostream>
#include <vector>
#include <netinet/in.h>

#include "Socket.hpp"

namespace ilrd
{
class TCP_Connect : public Socket
{
public:
    TCP_Connect(const char* port, const char* other_ip = NULL);
    explicit TCP_Connect(int fd);
    ~TCP_Connect();

    size_t Receive(std::vector<char>& buffer);
    void Send(const std::vector<char>& buffer) const;

};
}





#endif //ILRD_RD329_TCP_CONNECT_HPP
