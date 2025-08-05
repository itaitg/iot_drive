
//
// Created by bender on 3/27/25.
#ifndef  ILRD_RD1645_IINPUTPROXY_HPP
#define  ILRD_RD1645_IINPUTPROXY_HPP

#include "ATaskArgs.hpp"
#include "IListener.hpp"

namespace ilrd
{

class IInputProxy 
{
public:
    /// returns the arguments of the task
    /// @param fd_ file descriptor that woke up
    /// @param mode_ mode to react upon
    /// @return @ITaskArgs
    virtual std::shared_ptr<ATaskArgs> GetTaskArgs(int fd_, MODE mode_) = 0;

    virtual ~IInputProxy() = default;
    IInputProxy() = default;
    IInputProxy(const IInputProxy& other_) = delete;
    IInputProxy& operator=(const IInputProxy& other_) = delete;
    IInputProxy(IInputProxy&& other_) = delete;
    IInputProxy& operator=(IInputProxy&& other_) = delete;

};
}

#endif // ILRD_RD1645_IINPUTPROXY_HPP
