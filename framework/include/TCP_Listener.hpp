//
// Created by bender on 2/22/25.
//


#ifndef ILRD_RD329_TCP_SERVER_HPP
#define ILRD_RD329_TCP_SERVER_HPP

#include <vector>
#include "TCP_Connect.hpp"

#include "Socket.hpp"

namespace ilrd
{
class TCP_Listener : public Socket
{
public:
    explicit TCP_Listener(const char* port);
    ~TCP_Listener();


    TCP_Connect* Connect() const;
    static void Disconnect(const TCP_Connect* connection);

private:
    size_t Receive(std::vector<char>& buffer);
    void Send(const std::vector<char>& str) const;
};

}
#endif //ILRD_RD329_TCP_SERVER_HPP
