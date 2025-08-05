
//
// Created by bender on 3/25/25.
#ifndef  ILRD_RD1645_SCHEDULER_HPP
#define  ILRD_RD1645_SCHEDULER_HPP

#include <atomic>
#include <chrono>
#include <csignal>
#include <memory>
#include <queue>

#include "TimedTask.hpp"

namespace ilrd
{

class Scheduler 
{
public:
    friend class Handleton;
    ~Scheduler();
    Scheduler(const Scheduler& other_) = delete;
    Scheduler& operator=(const Scheduler& other_) = delete;
    Scheduler(Scheduler&& other_) = delete;
    Scheduler& operator=(Scheduler&& other_) = delete;
    /// add tasks to the scheduler (non blocking)
    /// @param task_ the task to run (can add more tasks)
    /// @param perform_in_ the absolute time to run in milliseconds
    void AddTask(const std::shared_ptr<ISchedulerTask>& task_,
                 const std::chrono::milliseconds& perform_in_);

private:
    class SchedulerTask;
    static void TimerThread(sigval arg);
    void ThreadLogic();
    Scheduler();
    void UpdateTimer(std::chrono::time_point<std::chrono::system_clock>
    new_task_time = std::chrono::high_resolution_clock::now());


    std::priority_queue<SchedulerTask> m_queue;
    timer_t m_timer;
    std::mutex m_lock;
    std::atomic_flag m_has_tasks;
    std::atomic_uint m_num_of_tasks;

    class SchedulerTask
    {
    public:
        explicit SchedulerTask(const std::shared_ptr<ISchedulerTask>& task_,
                const std::chrono::time_point<std::chrono::system_clock>& perform_in_);
        explicit SchedulerTask();
        void Run() const;
        bool operator<(const SchedulerTask& other_) const;
        const std::chrono::time_point<std::chrono::system_clock>& GetTime() const;
    private:
        std::shared_ptr<ISchedulerTask> m_task;
        std::chrono::time_point<std::chrono::system_clock> m_time;
    };
};

}

#endif // ILRD_RD1645_SCHEDULER_HPP
