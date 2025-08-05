//
// Created by bender on 3/26/25.

#include <iostream>

#include "ASyncInjection.hpp"
#include "Handleton.hpp"


bool func()
{
    static int num = 5;
    if(num--)
    {
        std::cout << num << std::endl;
        return true;
    }

    return false;
}


void ASyncInjectionTest()
{
    std::function<bool(void)> P3 = std::bind(&func);
    new ilrd::ASyncInjection(P3, std::chrono::milliseconds(1000));
}

int main()
{

    ASyncInjectionTest();

    return 0;
}
