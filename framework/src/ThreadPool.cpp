//
// Created by bender on 3/10/25.
// Approved by: Amit


//////////////////include

#include "ThreadPool.hpp"   //thread pool

enum SYS_PRIORITY
{
    KILL = 0,
    PAUSE = 4,
    REMOVE = 5
};

thread_local bool ilrd::ThreadPool::m_thread_is_running = true;
const std::shared_ptr<ilrd::ITPTask>
ilrd::ThreadPool::m_turn_off_task = std::make_shared<ilrd::threadpool::Function_Task<>>([] {m_thread_is_running = false;});

/////////////////ThreadPool

ilrd::ThreadPool::ThreadPool(const size_t num_of_threads_): m_is_sleeping(false),
    m_pausetask(new PauseTask(m_is_sleeping))
{
    for(size_t i = 0; i < num_of_threads_; ++i)
    {
        auto ptr = std::make_unique<std::jthread>([this] {RunThread();});
        m_thread_list[ptr->get_id()].swap(ptr);
    }
}

ilrd::ThreadPool::~ThreadPool()
{
    Resume();
    for(size_t i = 0; i < m_thread_list.size(); ++i)
    {
        AddTask(m_turn_off_task, static_cast<TASK_PRIORITY>(KILL));
    }
}

void ilrd::ThreadPool::AddTask(const std::shared_ptr<ITPTask>& task_,
    const TASK_PRIORITY priority_)
{
    const TPTask new_task(task_, priority_);
    m_queue.Push(new_task);
}

void ilrd::ThreadPool::IncreaseThreads(const size_t to_add_)
{
    for(size_t i = 0; i < to_add_; ++i)
    {
        if(m_is_sleeping)
        {
            AddTask(m_pausetask, static_cast<TASK_PRIORITY>(PAUSE));
        }
        auto ptr = std::make_unique<std::jthread>([this] {RunThread();});
        m_thread_list[ptr->get_id()].swap(ptr);
        if(m_is_sleeping)
        {
            m_pausetask->Acquire();
        }
    }
}

void ilrd::ThreadPool::DecreaseThreads(const size_t to_remove_)
{
    const bool former_status = m_is_sleeping;

    m_is_sleeping = false;
    for(size_t i = 0; i < to_remove_; ++i)
    {
        AddTask(m_turn_off_task, static_cast<TASK_PRIORITY>(REMOVE));
        m_pausetask->NotifyOne();
    }
    for(size_t i = 0; i < to_remove_; ++i)
    {
        std::jthread::id thread_id;
        m_to_remove.Pop(thread_id);
        m_thread_list.erase(thread_id);
    }
    m_is_sleeping = former_status;
}

void ilrd::ThreadPool::SetNumThread(const size_t num_of_threads_)
{
    if(num_of_threads_ > m_thread_list.size())
    {
        IncreaseThreads(num_of_threads_ - m_thread_list.size());
    }
    else
    {
        DecreaseThreads(m_thread_list.size() - num_of_threads_);
    }
}

void ilrd::ThreadPool::Pause()
{
    if(m_is_sleeping)
    {
        return;
    }

    m_is_sleeping = true;
    for(size_t i = 0; i < m_thread_list.size(); ++i)
    {
        AddTask(m_pausetask, static_cast<TASK_PRIORITY>(PAUSE));
    }
    for(size_t i = 0; i < m_thread_list.size(); ++i)
    {
        m_pausetask->Acquire();
    }
}

void ilrd::ThreadPool::Resume()
{
    m_is_sleeping = false;
    m_pausetask->Notify();
}

/////////////////TPTask

ilrd::ThreadPool::TPTask::TPTask(const std::shared_ptr<ITPTask>&
task_,const TASK_PRIORITY priority_): m_task(task_), m_priority(priority_),
    m_insert_time(std::chrono::high_resolution_clock::now())
{}

bool ilrd::ThreadPool::TPTask::operator<(const TPTask& other_) const
{
    return m_priority == other_.m_priority ?
        m_insert_time < other_.m_insert_time: m_priority < other_.m_priority;
}

void ilrd::ThreadPool::TPTask::Run()
{
    m_task->Run();
}

/////////////////PauseTask

ilrd::ThreadPool::PauseTask::PauseTask(const bool& is_sleeping_):  m_is_paused(is_sleeping_), m_pause_sync(0)
{}


void ilrd::ThreadPool::PauseTask::Run()
{
    m_pause_sync.release();
    std::unique_lock lock(m_pause_lock);
    m_cond_pause.wait(lock, [this] {return !m_is_paused;});
}

void ilrd::ThreadPool::PauseTask::Notify()
{
    std::unique_lock lock(m_pause_lock);
    m_cond_pause.notify_all();
}

void ilrd::ThreadPool::PauseTask::NotifyOne()
{
    std::unique_lock lock(m_pause_lock);
    m_cond_pause.notify_one();
}

void ilrd::ThreadPool::PauseTask::Acquire()
{
    m_pause_sync.acquire();
}

/////////////////


void ilrd::ThreadPool::RunThread()
{
    while(m_thread_is_running)
    {
        TPTask task;
        m_queue.Pop( task);
        task.Run();
    }
    m_to_remove.Push(std::this_thread::get_id());
}



