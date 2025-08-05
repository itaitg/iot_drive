//
// Created by bender on 2/22/25.
//

#ifndef ILRD_RD329_SOCKET_HPP
#define ILRD_RD329_SOCKET_HPP

#include <vector>
#include <netdb.h>

namespace ilrd
{
class Socket
{
public:
    int Getfd() const;
    virtual ~Socket();

protected:
    Socket(const char* port, const char* ip, int type);
    explicit Socket(int fd);
    virtual size_t Receive(std::vector<char>& buffer) = 0;
    virtual void Send(const std::vector<char>& str) const = 0;

    struct sockaddr* GetAddr() const;

    int m_socket_fd;

private:
    struct addrinfo* res;

};


}
#endif //ILRD_RD329_SOCKET_HPP

