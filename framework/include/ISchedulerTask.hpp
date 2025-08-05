
//
// Created by bender on 3/25/25.
#ifndef  ILRD_RD1645_ISCHEDULERTASK_HPP
#define  ILRD_RD1645_ISCHEDULERTASK_HPP

namespace ilrd
{

class ISchedulerTask
{
public:
    virtual void Run() = 0;
    ISchedulerTask (const ISchedulerTask& other_) = delete;
    ISchedulerTask& operator=(const ISchedulerTask & other_) = delete;
    ISchedulerTask (ISchedulerTask&& other_) = delete;
    ISchedulerTask& operator=(ISchedulerTask&& other_) = delete;
protected:
    ISchedulerTask () = default;
    virtual ~ISchedulerTask () = default;
};
}

#endif // ILRD_RD1645_ISCHEDULERTASK_HPP
