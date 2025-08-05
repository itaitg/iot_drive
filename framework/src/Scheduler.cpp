//
// Created by bender on 3/25/25.
// Approved by: Gil


//////////////////include

#include <mutex>

#include "Scheduler.hpp"

//////////////////static declarations

//////////////////constructors

//////////////////static implementations

///////////////////////////Scheduler

ilrd::Scheduler::Scheduler()
{
    sigevent timer_init{};
    timer_init.sigev_notify = SIGEV_THREAD;
    timer_init.sigev_notify_function = TimerThread;
    timer_init.sigev_value.sival_ptr = this;

    if(-1 == timer_create(CLOCK_REALTIME, &timer_init, &m_timer))
    {
        throw std::runtime_error("timer create");
    }
}

ilrd::Scheduler::~Scheduler()
{
    m_has_tasks.wait(true);
    timer_delete(m_timer);
}

void ilrd::Scheduler::UpdateTimer
(const std::chrono::time_point<std::chrono::system_clock>  new_task_time)
{
    if(m_num_of_tasks.load())
    {
        const auto next_time = m_queue.top().GetTime();
        if(new_task_time < next_time || m_queue.size() == 1 )
        {
            itimerspec next_interval = {};
            next_interval.it_value.tv_sec = std::chrono::system_clock::to_time_t(next_time);
            next_interval.it_value.tv_nsec = (next_time - std::chrono::system_clock::from_time_t(next_interval.it_value.tv_sec)).count();
            timer_settime(m_timer, TIMER_ABSTIME, &next_interval, nullptr);
        }
    }
    else
    {
        m_has_tasks.clear();
        m_has_tasks.notify_one();
    }
}

void ilrd::Scheduler::TimerThread(const sigval arg)
{
    static_cast<Scheduler*>(arg.sival_ptr)->ThreadLogic();
}

void ilrd::Scheduler::ThreadLogic()
{
    SchedulerTask task;

    {
        std::unique_lock lock(m_lock);
        task = m_queue.top();
        m_queue.pop();
    }
    task.Run();
    {
        std::unique_lock lock(m_lock);
        --m_num_of_tasks;
        UpdateTimer();
    }
}

void ilrd::Scheduler::AddTask(const std::shared_ptr<ISchedulerTask>& task_,
                              const std::chrono::milliseconds& perform_in_)
{
    const SchedulerTask new_task(task_, std::chrono::high_resolution_clock::now()
     + perform_in_);

    std::unique_lock lock(m_lock);
    m_queue.push(new_task);
    ++m_num_of_tasks;
    m_has_tasks.test_and_set();
    UpdateTimer(new_task.GetTime());
}

///////////////////////////SchedulerTask

ilrd::Scheduler::SchedulerTask::SchedulerTask(const std::shared_ptr<ISchedulerTask>& task_,
    const std::chrono::time_point<std::chrono::system_clock>& perform_in_): m_task(task_),
    m_time(perform_in_)
{}

ilrd::Scheduler::SchedulerTask::SchedulerTask(): m_task(nullptr)
{}

void ilrd::Scheduler::SchedulerTask::Run() const
{
    m_task->Run();
}

bool ilrd::Scheduler::SchedulerTask::operator<(const SchedulerTask& other_) const
{
    return m_time > other_.m_time;
}

const std::chrono::time_point<std::chrono::system_clock>&
ilrd::Scheduler::SchedulerTask::GetTime() const
{
    return m_time;
}

