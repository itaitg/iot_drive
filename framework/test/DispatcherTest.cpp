//
// Created by bender on 3/18/25.

#include <iostream>

#include "Dispatcher.hpp"

class producer
{
public:
    struct full
    {
        int a;
    };
    ilrd::Dispatcher<full> im_noti;
    void Noti();

};

void producer::Noti()
{
    full data = {4};
    im_noti.Notify(data);
}

class consumer1
{
public:
    void urnoti(producer::full data_)
    {
        std::cout << "first Callback " << data_.a << std::endl;
    }
};

class consumer2
{
public:
    void urnoti(producer::full data_)
    {
        std::cout << "second Callback " << data_.a << std::endl;
    }
};

class consumer3
{
public:
    void urnoti(producer::full data_)
    {
        std::cout << "third Callback " << data_.a << std::endl;
    }
    void unoti()
    {
        std::cout << "death of third Callback " << std::endl;
    }
};


void DispatcherTest()
{
    consumer1 cons1;
    consumer2 cons2;
    consumer3 cons3;

    ilrd::Callback<producer::full, consumer1> runoti1(cons1, &consumer1::urnoti);
    ilrd::Callback<producer::full, consumer2> runoti2(cons2, &consumer2::urnoti);
    ilrd::Callback<producer::full, consumer3> runoti3(cons3,
    &consumer3::urnoti, &consumer3::unoti);
    producer ofir;

    ofir.im_noti.Register(runoti1);
    ofir.im_noti.Register(runoti1);
    ofir.im_noti.Register(runoti2);
    ofir.im_noti.Register(runoti3);

    ofir.Noti();

    ofir.im_noti.Unregister(runoti1);
    ofir.im_noti.Unregister(runoti1);

    ofir.Noti();

}



int main()
{
    DispatcherTest();
    return 0;
}
