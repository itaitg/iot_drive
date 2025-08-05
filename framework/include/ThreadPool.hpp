
//
// Created by bender on 3/10/25.
#ifndef  ILRD_RD1645_THREADPOOL_HPP
#define  ILRD_RD1645_THREADPOOL_HPP



#include <map>                  //map
#include <thread>               //threads

#include "TPTask.hpp"           //tasks
#include "WaitableQueue.hpp"    //queue

namespace ilrd
{
enum TASK_PRIORITY
{
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};


///
/// manages threads that are able to receive and perform tasks in order of priority and time of insert
class ThreadPool
{
public:
    /// start and run the ThreadPool
    /// @param num_of_threads_ number of threads
    explicit ThreadPool(size_t num_of_threads_ = std::thread::hardware_concurrency() - 1);
    ~ThreadPool();
    /// adds tasks to the queue for the threads to perform
    /// @param task_ the task to add to the queue for the threads to run
    /// @param priority_ the priority of the task to be performed for @TASK_PRIORITY
    void AddTask(const std::shared_ptr<ITPTask>& task_, TASK_PRIORITY priority_ =
    MEDIUM);
    /// change the number of running threads
    /// blocking until number of threads ahs changed
    /// @param num_of_threads_ the number of threads to be running
    void SetNumThread(size_t num_of_threads_);
    ///
    /// Pause ALL the threads (does not perform tasks added prior)
    /// blocking until all threads are paused
    void Pause();
    ///
    /// Resumes the threads
    /// blocking until all the thread are active
    void Resume();

private:
    class TPTask;
    class PauseTask;

    bool m_is_sleeping;
    WaitableQueue<std::jthread::id> m_to_remove;
    WaitableQueue<TPTask, std::priority_queue<TPTask>> m_queue;
    std::map<std::thread::id, std::unique_ptr<std::jthread>> m_thread_list;
    std::shared_ptr<PauseTask> m_pausetask;
    static thread_local bool m_thread_is_running;
    static const std::shared_ptr<ITPTask> m_turn_off_task;

    void IncreaseThreads(size_t to_add_);
    void DecreaseThreads(size_t to_remove_);

    class TPTask
    {
    public:
        explicit TPTask(const std::shared_ptr<ITPTask>& task_ = nullptr,
        TASK_PRIORITY priority_ = LOW);
        bool operator<(const TPTask& other_)const;
        void Run();
    private:
        std::shared_ptr<ITPTask> m_task;
        TASK_PRIORITY m_priority;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_insert_time;
    };

    class PauseTask final: public ITPTask
    {
    public:
        explicit PauseTask(const bool& is_sleeping_);
        void Run() override;
        void Notify();
        void NotifyOne();
        void Acquire();
    private:
        const bool& m_is_paused;
        std::mutex m_pause_lock;
        std::condition_variable m_cond_pause;
        std::counting_semaphore<> m_pause_sync;
    };

    void RunThread();
};
}

#endif // ILRD_RD1645_THREADPOOL_HPP
