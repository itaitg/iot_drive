//
// Created by bender on 3/9/25.


#include <iostream>

#include "ThreadPool.hpp"
#include "ITPTask.hpp"
#include "test_macros.h"


void PrintInt(int a)
{
    std::cout << a << std::endl;
}

int PrintInts(int a, int b)
{
    sleep(1);
    return a + b;
}


int main()
{

    ilrd::ThreadPool threadPool(2);


    std::function<void(void)> sumFunc5 = std::bind(&PrintInt, 5);
    std::function<void(void)> sumFunc6 = std::bind(&PrintInt, 6);
    std::function<int(void)> sumFunc7 = std::bind(&PrintInts, 7, 5);

    std::shared_ptr<ilrd::ITPTask> func5(new ilrd::threadpool::Function_Task (sumFunc5));
    std::shared_ptr<ilrd::ITPTask> func6(new ilrd::threadpool::Function_Task (sumFunc6));
    std::shared_ptr<ilrd::ITPTask> func7(new ilrd::threadpool::Future_Task (sumFunc7));


    threadPool.SetNumThread(4);
    threadPool.SetNumThread(2);

    size_t counter = 10;
    int a = 0;
    while(counter--)
    {
        threadPool.AddTask(func7, ilrd::HIGH);
        threadPool.AddTask(func6, ilrd::LOW);
        threadPool.AddTask(func5, ilrd::HIGH);
        a = static_cast<ilrd::threadpool::Future_Task<int>*>(func7.get())->Get();
        std::cout << a << std::endl;
    }
    threadPool.SetNumThread(4);
    threadPool.Pause();
    threadPool.AddTask(func6, ilrd::HIGH);
    threadPool.SetNumThread(2);
    threadPool.SetNumThread(4);
    sleep(5);



    PASS;
    return 0;
}
