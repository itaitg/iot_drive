//
// Created by bender on 3/13/25.


#include <thread>
#include <iostream>

#include "Singleton.hpp"

void ThreadFunca()
{
    size_t counter = 10;
    while(counter--)
    {
       ilrd::Singleton<std::string>::GetInstance()->append("a");
    }
}

void ThreadFuncb()
{
    size_t counter = 10;
    while(counter--)
    {
        std::cout << ilrd::Singleton<std::string>::GetInstance()->c_str() << std::endl;
    }
}

int main()
{
    std::jthread threadsb(ThreadFuncb);
    std::jthread threadsa(ThreadFunca);


    ilrd::Singleton<std::string>::GetInstance();
    //ilrd::Singleton<std::string>::Destruct();

    return 0;
}
