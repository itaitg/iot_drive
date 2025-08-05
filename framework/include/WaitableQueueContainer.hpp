//
// Created by bender on 3/15/25.
//

#ifndef ILRD_R1645_WAITABLE_QUEUE_CONTAINER_HPP
#define ILRD_R1645_WAITABLE_QUEUE_CONTAINER_HPP

#include <queue>

namespace ilrd
{

template<typename ElementType, typename QueueType>
class WaitableQueueContainer
{
public:
    //removes the next value int @val_
    void Pop(ElementType& val_);
    // add a value into the queue @val_
    void Push(const ElementType& val_);
    //check if the queue is empty
    bool IsEmpty() const;

private:

    QueueType m_queue;

};

template<typename ElementType>
class WaitableQueueContainer<ElementType, std::priority_queue<ElementType>>
{
public:
    //removes the next value int @val_
    void Pop(ElementType& val_);
    // add a value into the queue @val_
    void Push(const ElementType& val_);
    //check if the queue is empty
    bool IsEmpty() const;

private:

    std::priority_queue<ElementType> m_queue;
};

template<typename ElementType, typename QueueType>
void WaitableQueueContainer<ElementType, QueueType>::Pop(ElementType& val_)
{
    val_ = m_queue.front();
    m_queue.pop();
}


template<typename ElementType, typename QueueType>
void WaitableQueueContainer<ElementType, QueueType>::Push(const ElementType& val_)
{
      m_queue.push(val_);
}

template<typename ElementType, typename QueueType>
bool WaitableQueueContainer<ElementType, QueueType>::IsEmpty() const
{
    return m_queue.empty();
}


template<typename ElementType>
void WaitableQueueContainer<ElementType,std::priority_queue<ElementType>>::Pop(ElementType& val_)
{
    val_ = m_queue.top();
    m_queue.pop();
}

template<typename ElementType>
void WaitableQueueContainer<ElementType,std::priority_queue<ElementType>>::Push(const ElementType& val_)
{
    m_queue.push(val_);
}

template<typename ElementType>
bool WaitableQueueContainer<ElementType,std::priority_queue<ElementType>>::IsEmpty() const
{
    return m_queue.empty();
}

}


#endif //ILRD_R1645_WAITABLE_QUEUE_CONTAINER_HPP

