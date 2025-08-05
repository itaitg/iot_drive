//
// Created by bender on 3/23/25.

#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "Reactor.hpp"



void WriteToFd(int fd, ilrd::MODE mode)
{
    (void)mode;
    write(fd, "write", 6);
}

void ReadFromFd(int fd, ilrd::MODE mode)
{
    (void)mode;

    char arr[255] = {0};
    int size = read(fd, arr, 6);
    (void)size;
    std::cout << arr << std::endl;
}

void ReactorTest()
{
    ilrd::Reactor reactor;
    int fd = open("test.txt", O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR);
    if(fd == -1)
    {
        throw;
    }

    reactor.Register(STDIN_FILENO, ilrd::READ, [&reactor](int, ilrd::MODE) {reactor.Stop();});
    //reactor.Register(fd, ilrd::READ, ReadFromFd);
    //reactor.Register(fd, ilrd::WRITE, WriteToFd);
    reactor.Run();
}

int main()
{

    ReactorTest();

    return 0;
}
