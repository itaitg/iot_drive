
//
// Created by bender on 3/26/25.
#ifndef  ILRD_RD1645_ASYNCINJECTION_HPP
#define  ILRD_RD1645_ASYNCINJECTION_HPP

#include <chrono>
#include <functional>

#include <ISchedulerTask.hpp>
#include <memory>

namespace ilrd
{

class ASyncInjection 
{
public:
    ///
    /// @param func_ function for repetitive tasks, will return TRUE to run again
    /// FALSE to stop running
    /// @param interval_ the time frame that the function will run again
    ASyncInjection(const std::function<bool()>& func_,
                   const std::chrono::milliseconds& interval_);

    ASyncInjection(const ASyncInjection& other_) = delete;
    ASyncInjection& operator=(const ASyncInjection& other_) = delete;
    ASyncInjection(ASyncInjection&& other_) = delete;
    ASyncInjection& operator=(ASyncInjection&& other_) = delete;
private:
    friend class Handleton;
    class ASyncInjectionTask;
    ~ASyncInjection() = default;
    void PerformAction();
    std::function<bool()> m_Func;
    std::chrono::milliseconds m_interval;
    std::shared_ptr<ASyncInjectionTask> m_task;

    class ASyncInjectionTask final : public ISchedulerTask
    {
    public:
        explicit ASyncInjectionTask(ASyncInjection& task_);
        ~ASyncInjectionTask() override = default;
        ASyncInjectionTask(const ASyncInjectionTask& other_) = delete;
        ASyncInjectionTask& operator=(const ASyncInjectionTask& other_) = delete;
        ASyncInjectionTask(ASyncInjectionTask&& other_) = delete;
        ASyncInjectionTask& operator=(ASyncInjectionTask&& other_) = delete;

        void Run() override;

    private:
        ASyncInjection& m_task;
    };

};
}

#endif // ILRD_RD1645_ASYNCINJECTION_HPP
