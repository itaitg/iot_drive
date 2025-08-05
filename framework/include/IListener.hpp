
//
// Created by bender on 3/23/25.
#ifndef  ILRD_RD1645_ILISTENER_HPP
#define  ILRD_RD1645_ILISTENER_HPP

#include <vector>

namespace ilrd
{
    enum MODE
    {
        READ,
        WRITE
    };

class IListener
{
public:
    virtual ~IListener() = default;
    IListener(const IListener& other_) = delete;
    IListener& operator=(const IListener& other_) = delete;
    IListener(IListener&& other_) = delete;
    IListener& operator=(IListener&& other_) = delete;

    virtual std::vector<std::pair<int,MODE>> Listen(std::vector<std::pair<int,
            MODE>> list_) = 0;

protected:
    IListener() = default;
};
}

#endif // ILRD_RD1645_ILISTENER_HPP
