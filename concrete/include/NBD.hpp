
//
// Created by bender on 4/22/25.
#ifndef  ILRD_RD1645_NBD_HPP
#define  ILRD_RD1645_NBD_HPP

#include <csignal>
#include <optional>
#include <sys/types.h>

#include "TCP_Connect.hpp"

namespace ilrd
{

class NBD 
{
public:
    NBD();
    ~NBD();
    void Init(const char* dev_file);
    TCP_Connect& GetTCP();

    NBD(const NBD& other_) = delete;
    NBD& operator=(const NBD& other_) = delete;
    NBD(NBD&& other_) = delete;
    NBD& operator=(NBD&& other_) = delete;
    static u_int64_t ntohll(u_int64_t a);
private:
    int set_sigaction(int sig, const struct sigaction * act);
    static void disconnect_nbd(int signal);
    int write_all(int fd, char* buf, size_t count);
    int read_all(int fd, char* buf, size_t count);

    std::optional<TCP_Connect> m_server;
    static int m_nbd_dev;
    pid_t m_child;
};
}
#endif // ILRD_RD1645_NBD_HPP
