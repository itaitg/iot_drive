//
// Created by bender on 4/23/25.
// Approved by:


#include <fstream>

int main()
{
    std::ofstream file{"a.data"};
    for (size_t i = 0; i < 8*1024*1024; ++i)
    {
        file << '\0';
    }
    return 0;
}
