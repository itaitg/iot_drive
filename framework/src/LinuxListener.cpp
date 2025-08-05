//
// Created by bender on 3/23/25.
// Approved by:


#include <sys/socket.h>

//////////////////include

#include "LinuxListener.hpp"
//////////////////static declarations

//////////////////constructors

//////////////////static implementations



std::vector<std::pair<int,ilrd::MODE>> ilrd::LinuxListener::Listen
            (const std::vector<std::pair<int,MODE>> list_)
{
    fd_set read_fd;
    fd_set write_fd;

    FD_ZERO(&read_fd);
    FD_ZERO(&write_fd);

    auto list_iter = list_.begin();

    int max_fd = 0;
    while(list_iter != list_.end())
    {
        max_fd = std::max(max_fd, list_iter->first);
        if(list_iter->second == READ)
        {
            FD_SET(list_iter->first, &read_fd);
        }
        else if(list_iter->second == WRITE)
        {
            FD_SET(list_iter->first, &write_fd);
        }
        ++list_iter;
    }
    const int fds_to_read = select(max_fd + 1, &read_fd,
        &write_fd,nullptr,nullptr);

    std::vector<std::pair<int,MODE>> return_val;
    if(fds_to_read != 0)
    {
        list_iter = list_.begin();

        while(list_iter != list_.end())
        {
            if(FD_ISSET(list_iter->first, &write_fd) || FD_ISSET(list_iter->first, &read_fd))
            {
                return_val.emplace_back(list_iter->first, list_iter->second);
            }
            ++list_iter;
        }
    }
    return return_val;
}


