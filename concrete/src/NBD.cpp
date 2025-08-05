//
// Created by bender on 4/22/25.
// Approved by:


//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations


#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <err.h>
#include <fcntl.h>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/wait.h>


#include "NBD.hpp"

#include <stdexcept>


#ifndef BUSE_DEBUG
#define BUSE_DEBUG (0)
#endif


int ilrd::NBD::read_all(int fd, char* buf, size_t count)
{
    int bytes_read;

    while(count > 0)
    {
        bytes_read = read(fd, buf, count);
        assert(bytes_read > 0);
        buf += bytes_read;
        count -= bytes_read;
    }
    assert(count == 0);

    return 0;
}

int ilrd::NBD::write_all(int fd, char* buf, size_t count)
{
    int bytes_written;

    while(count > 0)
    {
        bytes_written = write(fd, buf, count);
        assert(bytes_written > 0);
        buf += bytes_written;
        count -= bytes_written;
    }
    assert(count == 0);

    return 0;
}

/* Signal handler to gracefully disconnect from nbd kernel driver. */
int ilrd::NBD::m_nbd_dev = -1;

void ilrd::NBD::disconnect_nbd(int signal)
{
    (void)signal;
    if(m_nbd_dev != -1)
    {
        if(ioctl(m_nbd_dev, NBD_DISCONNECT) == -1)
        {
            warn("failed to request disconect on nbd device");
        }
        else
        {
            m_nbd_dev = -1;
            fprintf(stderr, "sucessfuly requested disconnect on nbd device\n");
        }
    }
}

/* Sets signal action like regular sigaction but is suspicious. */
int ilrd::NBD::set_sigaction(int sig, const struct sigaction* act)
{
    struct sigaction oact;
    int r = sigaction(sig, act, &oact);
    if(r == 0 && oact.sa_handler != SIG_DFL)
    {
        warnx("overriden non-default signal handler (%d: %s)", sig,
              strsignal(sig));
    }
    return r;
}


/////////////////////////////////////////////////////////////////

#ifdef WORDS_BIGENDIAN
u_int64_t ilrd::NBD::ntohll(u_int64_t a)
{
  return a;
}
#else
u_int64_t ilrd::NBD::ntohll(u_int64_t a)
{
    u_int32_t lo = a & 0xffffffff;
    u_int32_t hi = a >> 32U;
    lo = ntohl(lo);
    hi = ntohl(hi);
    return ((u_int64_t)lo) << 32U | hi;
}
#endif
#define htonll ntohll


ilrd::NBD::NBD(): m_child()
{}

ilrd::NBD::~NBD()
{
    if(m_child && waitpid(m_child, nullptr, 0) == -1)
    {
        warn("waitpid failed");
    }
}

void ilrd::NBD::Init(const char* dev_file)
{
    int nbd, err;
    int sp[2];

    err = socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
    assert(!err);
    nbd = open(dev_file, O_RDWR);
    if(nbd == -1)
    {
        fprintf(stderr,
                "Failed to open `%s': %s\n"
                "Is kernel module `nbd' loaded and you have permissions "
                "to access the device?\n", dev_file, strerror(errno));
        throw std::runtime_error("");
    }
    uint64_t val = 4*1024*1024;
    err = ioctl(nbd, NBD_SET_SIZE, val);
    assert(err != -1);
    err = ioctl(nbd, NBD_CLEAR_SOCK);

    assert(err != -1);

    m_child = fork();
    if(m_child == 0)
    {
        /* Block all signals to not get interrupted in ioctl(NBD_DO_IT), as
         * it seems there is no good way to handle such interruption.*/
        sigset_t sigset;
        if(
            sigfillset(&sigset) != 0 ||
            sigprocmask(SIG_SETMASK, &sigset, NULL) != 0
        )
        {
            throw std::runtime_error("failed to block signals in child");
        }

        /* The child needs to continue setting things up. */
        // close(sp[0]);
        int sk = sp[1];

        if(ioctl(nbd, NBD_SET_SOCK, sk) == -1)
        {
            fprintf(stderr, "ioctl(nbd, NBD_SET_SOCK, sk) failed.[%s]\n",
                    strerror(errno));
            throw std::runtime_error("");
        }
        err = ioctl(nbd, NBD_DO_IT);
        if(BUSE_DEBUG) fprintf(stderr, "nbd device terminated with code %d\n",
                               err);
        std::cout << "Nbd exit\n";
        if(err == -1)
        {
            throw std::runtime_error("NBD_DO_IT terminated with error");
        }

        if(
            ioctl(nbd, NBD_CLEAR_QUE) == -1 ||
            ioctl(nbd, NBD_CLEAR_SOCK) == -1
        )
        {
            throw std::runtime_error("failed to perform nbd cleanup actions");
        }
        exit(0);
    }

    /* Parent handles termination signals by terminating nbd device. */
    assert(m_nbd_dev == -1);
    m_nbd_dev = nbd;
    struct sigaction act;
    act.sa_handler = &disconnect_nbd;
    act.sa_flags = SA_RESTART;
    if(
        sigemptyset(&act.sa_mask) != 0 ||
        sigaddset(&act.sa_mask, SIGINT) != 0 ||
        sigaddset(&act.sa_mask, SIGTERM) != 0
    )
    {
        throw std::runtime_error("failed to prepare signal mask in parent");
    }
    if(
        set_sigaction(SIGINT, &act) != 0 ||
        set_sigaction(SIGTERM, &act) != 0
    )
    {
        throw std::runtime_error("failed to register signal handlers in parent");
    }

    //close(sp[1]);
    m_server.emplace(sp[0]);
    /* serve NBD socket */
    // int status;
    // status = serve_nbd(userdata);

}

ilrd::TCP_Connect& ilrd::NBD::GetTCP()
{
    return *m_server;
}


