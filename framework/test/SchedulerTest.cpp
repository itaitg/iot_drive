//
// Created by bender on 3/25/25.

#include <iostream>

#include "Handleton.hpp"
#include "Scheduler.hpp"
#include "TimedTask.hpp"

void print1(void)
{
    std::cout << "1" << std::endl;
}

void print2()
{
    //sleep(10);
    std::cout << "2" << std::endl;
}

void print3()
{

    std::cout << "3" << std::endl;
}

void SchedulerTest()
{

    std::function<void(void)> P1 = std::bind(&print1);
    std::function<void(void)> P2 = std::bind(&print2);
    std::function<void(void)> P3 = std::bind(&print3);

    std::shared_ptr<ilrd::ISchedulerTask> func1(new ilrd::TimedTask(P1));
    std::shared_ptr<ilrd::ISchedulerTask> func2(new ilrd::TimedTask(P2));
    std::shared_ptr<ilrd::ISchedulerTask> func3(new ilrd::TimedTask(P3));


    ilrd::Handleton::GetInstance<ilrd::Scheduler>()->AddTask(func1, std::chrono::milliseconds(5000));
    ilrd::Handleton::GetInstance<ilrd::Scheduler>()->AddTask(func2, std::chrono::milliseconds(1000));
    sleep(1);
    // ilrd::Handleton::GetInstance<ilrd::Scheduler>()->AddTask(func3, std::chrono::milliseconds(5));
    // ilrd::Handleton::GetInstance<ilrd::Scheduler>()->AddTask(func2, std::chrono::milliseconds(1000));

}

int main()
{

    SchedulerTest();

    return 0;
}
