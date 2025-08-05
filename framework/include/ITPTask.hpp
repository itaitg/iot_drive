
//
// Created by bender on 3/27/25.
#ifndef  ILRD_RD1645_ITPTASK_HPP
#define  ILRD_RD1645_ITPTASK_HPP

namespace ilrd
///
///Interface for @ThreadPool tasks
{
class ITPTask
{
public:
    virtual void Run() = 0;
protected:
    virtual ~ITPTask() = default;
};
}
#endif // ILRD_RD1645_ITPTASK_HPP
