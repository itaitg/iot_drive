//
// Created by bender on 3/17/25.

#include <iostream>
#include <dlfcn.h>

#include "Handleton.hpp"


void HandletonTest()
{
    void* handle1 = dlopen("libHandletondll1.so", RTLD_LAZY);
    void* handle2 = dlopen("libHandletondll2.so", RTLD_LAZY);

    void* Func1 = dlsym(handle1, "Do");
    void* Func2 = dlsym(handle2, "Do2");

    reinterpret_cast<void (*)()>(Func1)();
    reinterpret_cast<void (*)()>(Func2)();
    std::cout << ilrd::Handleton::GetInstance<int>() << std::endl;

    dlclose(handle1);
    dlclose(handle2);

}


int main()
{
    HandletonTest();
    return 0;
}
