
//
// Created by bender on 3/13/25.
#ifndef  ILRD_RD1645_SINGLETON_HPP
#define  ILRD_RD1645_SINGLETON_HPP

#include <atomic>
#include <cstdlib>
#include <mutex>

namespace ilrd
{


template <typename T>
class Singleton
{
public:
    Singleton() = delete;
    Singleton(const Singleton& other_) = delete;
    Singleton& operator=(const Singleton& other_) = delete;
    ~Singleton() = delete;

    static T* GetInstance();

private:
    static std::atomic<T*> m_instance;
    static void Destruct();
};

template <typename T>
std::atomic<T*> Singleton<T>::m_instance = nullptr;

template <typename T>
T* Singleton<T>::GetInstance()
{
    T* temp = m_instance.load(std::memory_order_acquire);
    if(!temp)
    {
        std::atomic_thread_fence(std::memory_order_acquire);
        temp = m_instance.load(std::memory_order_relaxed);
        if(!temp)
        {
            temp = new T();
            m_instance.store(temp, std::memory_order_release);
            std::atexit(Destruct);
        }
    }

    return m_instance;
}

template <typename T>
void Singleton<T>::Destruct()
{
    std::atomic_thread_fence(std::memory_order_acquire);
    delete m_instance.load();

    m_instance = nullptr;
    std::atomic_thread_fence(std::memory_order_release);

}
}


#endif // ILRD_RD1645_SINGLETON_HPP
