//
// Created by bender on 3/22/25.
//


#include <iostream>


__attribute__((constructor))
void Start()
{
    std::cout << "Loaded" << std::endl;
}


__attribute__((destructor))
void END()
{
    std::cout << "Removed" << std::endl;
}