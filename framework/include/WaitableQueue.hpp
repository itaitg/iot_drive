
// Created by bender on 3/6/25.
#ifndef  ILRD_RD1645_WAITABLEQUEUE_HPP
#define  ILRD_RD1645_WAITABLEQUEUE_HPP


 #include <condition_variable>
 #include <mutex>


#include "WaitableQueueContainer.hpp"

namespace ilrd
{


template<typename ElementType, typename QueueType = std::queue<ElementType>>
class WaitableQueue: private WaitableQueueContainer<ElementType, QueueType>
{
public:
    //removes the next value int @val_
    void Pop(ElementType& val_);
    //try to remove the next value int @val_ for a specific time
    bool Pop(std::chrono::milliseconds timeout_, ElementType& val_);
    // add a value into the queue @val_
    void Push(const ElementType& val_);
    //check if the queue is empty
    bool IsEmpty() const;

private:
    mutable std::timed_mutex m_lock;
    std::condition_variable_any m_cond;
};

template<typename ElementType,typename QueueType>
void WaitableQueue<ElementType, QueueType>::Pop(ElementType& val_)
{
    std::unique_lock lock(m_lock);

    m_cond.wait(lock, [this] {return !WaitableQueueContainer<ElementType, QueueType>::IsEmpty();});

    WaitableQueueContainer<ElementType, QueueType>::Pop(val_);
}

template <typename ElementType, typename QueueType>
bool WaitableQueue<ElementType, QueueType>::Pop(const std::chrono::milliseconds timeout_, ElementType& val_)
{
    const auto start = std::chrono::steady_clock::now();
    std::unique_lock lock(m_lock, timeout_);

    const auto end = std::chrono::steady_clock::now();
    auto waiting_time = timeout_ - std::chrono::duration_cast<std::chrono::milliseconds>
    (end - start);


    if(!m_cond.wait_for(lock, waiting_time, [this] {return !WaitableQueueContainer<ElementType, QueueType>::IsEmpty();}))
    {
        return false;
    }

    WaitableQueueContainer<ElementType, QueueType>::Pop(val_);

    return true;
}

template <typename ElementType, typename QueueType>
void WaitableQueue<ElementType, QueueType>::Push(const ElementType& val_)
{
    {
        std::unique_lock lock(m_lock);
        WaitableQueueContainer<ElementType, QueueType>::Push(val_);
    }
    m_cond.notify_one();
}

template <typename ElementType, typename QueueType>
bool WaitableQueue<ElementType, QueueType>::IsEmpty() const
{
    std::unique_lock lock(m_lock);

    return WaitableQueueContainer<ElementType, QueueType>::IsEmpty();
}


}



#endif //ILRD_RD1645_WAITABLEQUEUE_HPP
