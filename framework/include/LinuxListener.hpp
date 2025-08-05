
//
// Created by bender on 3/24/25.
#ifndef  ILRD_RD1645_LINUXLISTENER_HPP
#define  ILRD_RD1645_LINUXLISTENER_HPP

#include "IListener.hpp"

namespace ilrd
{

class LinuxListener final : public IListener
{
public:
    LinuxListener()  = default;
    ~LinuxListener() override = default ;
    LinuxListener(const LinuxListener& other_) = delete;
    LinuxListener& operator=(const LinuxListener& other_) = delete;
    LinuxListener(LinuxListener&& other_) = delete;
    LinuxListener& operator=(LinuxListener&& other_) = delete;

    std::vector<std::pair<int,MODE>> Listen(std::vector<std::pair<int,
            MODE>> list_) override;

};
}

#endif // ILRD_RD1645_LINUXLISTENER_HPP
