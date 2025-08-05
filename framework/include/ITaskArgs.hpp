
//
// Created by bender on 3/27/25.
#ifndef  ILRD_RD1645_ITASKARGS_HPP
#define  ILRD_RD1645_ITASKARGS_HPP



namespace ilrd
{

class ITaskArgs 
{
public:
    /// return the key associated with the arguments of the task
    virtual int GetKey() = 0;
    ITaskArgs() = default;
    virtual ~ITaskArgs() = default;

    ITaskArgs(const ITaskArgs& other_) = delete;
    ITaskArgs& operator=(const ITaskArgs& other_) = delete;
    ITaskArgs(ITaskArgs&& other_) = delete;
    ITaskArgs& operator=(ITaskArgs&& other_) = delete;

};
}

#endif // ILRD_RD1645_ITASKARGS_HPP
