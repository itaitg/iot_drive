
#include <iostream>
#include <bits/shared_ptr.h>

#include "Factory.hpp"
#include "Handleton.hpp"

class Base
{
public:
    virtual ~Base() = default;
    static std::shared_ptr<Base> Create(size_t i = 0, int j = 0);
    virtual void Do() = 0;
};

class Der1 : public Base
{
public:
    void Do() override { std::cout << "Der1" << std::endl; }
};

class Der2 : public Base
{
public:
    void Do() override { std::cout << "Der2" << std::endl; }
};

std::shared_ptr<Base> Base::Create(size_t i, int j)
{
    std::cout << j << std::endl;
    if(i==1)
    {

        return std::make_shared<Der1>();
    }
    return std::make_shared<Der2>();
}

std::shared_ptr<Base> NullCreate(size_t i, int j)
{
    return nullptr;
}

void TestFactory()
{
    auto baseFactory = ilrd::Handleton::GetInstance<ilrd::Factory<int, Base, size_t, int>>();
    baseFactory->Register(5, Base::Create);
    baseFactory->Register(10, Base::Create);
    baseFactory->Register(0, NullCreate);

    std::shared_ptr<Base> arr[10];
    for (int i = 0; i < 10; i++)
    {
        if (i%3 == 0)
        {
            arr[i] = baseFactory->Create(5, 0, 4);
        }
        else if (i%3 ==1)
        {
            arr[i] = baseFactory->Create(10, 1, 3);
        }
        else
        {
            arr[i] = baseFactory->Create(0, 1, 2);
        }
    }

    try
    {
        auto ptr = baseFactory->Create(2, 0, 4);
    }
    catch ([[maybe_unused]] const std::exception& e) {}

    for (const std::shared_ptr<Base>& b : arr)
    {
        if (b != nullptr)
        {
            b->Do();
        }
    }

}

int main()
{
    TestFactory();
    return 0;
}