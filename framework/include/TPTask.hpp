
//
// Created by bender on 3/9/25.
#ifndef  ILRD_RD1645_TPTASK_HPP
#define  ILRD_RD1645_TPTASK_HPP


#include <functional>
#include <semaphore>

#include"ITPTask.hpp"

namespace ilrd
{
namespace threadpool
{
/// function to run by the threads of @ThreadPool
/// @tparam ARGS arguments to be received by the function, leave blank for none
template<typename ...ARGS>
class Function_Task final: public ITPTask
{
public:
    ///
    /// @param func_ function to be run
    /// @param arguments_ arguments to be run with the function
    explicit Function_Task(std::function<void(ARGS...)> func_, ARGS... arguments_);
    void Run() override;
    ~Function_Task() override = default;
private:
    std::tuple<ARGS...> m_arguments;
    std::function<void(ARGS...)> m_func;
};

template <typename ...ARGS>
Function_Task<ARGS...>::Function_Task(std::function<void(ARGS...)> func_, ARGS... arguments_): m_arguments(arguments_...), m_func(func_)
{}

template <typename ...ARGS>
void Function_Task<ARGS...>::Run()
{
    std::apply(m_func, m_arguments);
}

/// function to run by the threads of @ThreadPool
/// function should return a value
/// @tparam RETURN return type
/// @tparam ARGS arguments to be received by the function, leave blank for none
template<typename RETURN, typename ...ARGS>
class Future_Task final: public ITPTask
{
public:
    ///
    /// @param func_ function to be run
    /// @param arguments_ arguments to be run with the function
    explicit Future_Task(std::function<RETURN(ARGS...)> func_, ARGS... arguments_);
    /// gets the return value from the function (blocking)
    /// @return the return type
    RETURN Get();
    void Run() override;
    ~Future_Task() override = default;
private:
    std::tuple<ARGS...> m_arguments;
    std::function<RETURN(ARGS...)> m_func;
    std::binary_semaphore m_sem;
    RETURN m_value;
};


template<typename RETURN, typename ...ARGS>
Future_Task<RETURN, ARGS...>::Future_Task(std::function<RETURN(ARGS...)>
func_, ARGS... arguments_): m_arguments(arguments_...), m_func(func_),m_sem
(0) ,
m_value() {}

template<typename RETURN, typename ...ARGS>
void Future_Task<RETURN, ARGS...>::Run()
{
    m_value = std::apply(m_func, m_arguments);
    m_sem.release();
}

template<typename RETURN, typename ...ARGS>
RETURN Future_Task<RETURN, ARGS...>::Get()
{
    m_sem.acquire();

    return m_value;
}
}
}

#endif // ILRD_RD1645_TPTASK_HPP
