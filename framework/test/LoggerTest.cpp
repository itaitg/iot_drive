//
// Created by bender on 3/17/25.



#include "Logger.hpp"
#include "Handleton.hpp"

int main()
{
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log("1", ilrd::Logger::SEVERITY::DEBUG);
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log("2", ilrd::Logger::SEVERITY::DEBUG);
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log("3", ilrd::Logger::SEVERITY::DEBUG);
    ilrd::Handleton::GetInstance<ilrd::Logger>()->Log("5", ilrd::Logger::SEVERITY::DEBUG);


    return 0;
}
