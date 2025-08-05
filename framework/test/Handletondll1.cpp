//
// Created by bender on 3/17/25.
// Approved by:

#include <iostream>

#include "Handleton.hpp"

extern "C" void Do()
{
    std::cout << ilrd::Handleton::GetInstance<int>() << std::endl;
}