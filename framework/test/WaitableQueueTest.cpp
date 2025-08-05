//
// Created by bender on 3/6/25.


#include <iostream>
#include <thread>

#include "test_macros.h"
#include "WaitableQueue.hpp"

template <typename Q>
void Reader(ilrd::WaitableQueue<int, Q>& q)
{
    int val = 0;
    if(rand() % 2)
    {
        std::chrono::milliseconds timeout(1000);
        if(!q.Pop(timeout, val))
        {
            std::cout << "Q is empty" <<std::endl;
        }
        else
        {
            std::cout << val <<std::endl;
        }
    }
    else
    {
        q.Pop(val);
        std::cout << val <<std::endl;
    }

}

template <typename Q>
void Writer(ilrd::WaitableQueue<int, Q>& q)
{
    static int num = 0;

    sleep(1);
    q.Push(num++);

}


void QueueTest()
{
    ilrd::WaitableQueue<int> Q;


    TEST("isempty", Q.IsEmpty(), true);

    const int thread_count = 10;
    std::thread reader[thread_count];
    std::thread writer[thread_count];

    for(int i = 0; i < thread_count; ++i)
    {
        reader[i] = std::thread([&Q](){Reader(Q);});
        writer[i] = std::thread([&Q](){Writer(Q);});

    }
    for(int i = 0; i < thread_count; ++i)
    {
        reader[i].join();
        writer[i].join();
    }

}


void PQueueTest()
{
    ilrd::WaitableQueue<int, std::priority_queue<int>> PQ;

    TEST("isempty", PQ.IsEmpty(), true);

    const int thread_count = 10;
    std::thread reader[thread_count];
    std::thread writer[thread_count];

    for(int i = 0; i < thread_count; ++i)
    {
        reader[i] = std::thread([&PQ](){Reader(PQ);});
        writer[i] = std::thread([&PQ](){Writer(PQ);});
    }
    for(int i = 0; i < thread_count; ++i)
    {
        reader[i].join();
        writer[i].join();
    }
}


int main()
{
    QueueTest();
    PQueueTest();
    PASS;
    return 0;
}
