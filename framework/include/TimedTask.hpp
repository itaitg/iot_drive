
//
// Created by bender on 3/25/25.
#ifndef  ILRD_RD1645_SCHEDULERTASK_HPP
#define  ILRD_RD1645_SCHEDULERTASK_HPP

#include <functional>

#include "ISchedulerTask.hpp"

namespace ilrd
{

template<typename ...ARGS>
class TimedTask: public ISchedulerTask
{
public:
    explicit TimedTask(std::function<void(ARGS...)> func_, ARGS... arguments_);

    void Run() override;

    ~TimedTask() override = default;
    TimedTask(const TimedTask& other_) = delete;
    TimedTask& operator=(const TimedTask& other_) = delete;
    TimedTask(TimedTask&& other_) = delete;
    TimedTask& operator=(TimedTask&& other_) = delete;
private:
    std::tuple<ARGS...> m_arguments;
    std::function<void(ARGS...)> m_func;
};

template <typename ... ARGS>
TimedTask<ARGS...>::TimedTask(std::function<void(ARGS...)> func_,
    ARGS... arguments_): m_arguments(arguments_...), m_func(func_)
{}

template <typename ... ARGS>
void TimedTask<ARGS...>::Run()
{
    std::apply(m_func, m_arguments);
}

}

#endif // ILRD_RD1645_SCHEDULERTASK_HPP
