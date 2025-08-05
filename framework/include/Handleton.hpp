
//
// Created by bender on 3/17/25.
#ifndef  ILRD_RD1645_HANDLETON_HPP
#define  ILRD_RD1645_HANDLETON_HPP

#include <memory>
#include <mutex>
#include <unordered_map>


namespace ilrd
{
class Handleton
{
public:
    template <typename T>
    static T* GetInstance();
    explicit Handleton() = delete;
    ~Handleton() = delete;
    Handleton(const Handleton& other_) = delete;
    Handleton& operator=(const Handleton& rhs_) = delete;
    Handleton(Handleton&& other_) = delete;
    Handleton& operator=(Handleton&& other_) = delete;

private:
    class HashFunc
    {
    public:
        size_t operator()(const std::type_info* id) const
        {
            return id->hash_code();
        }
    };

    class EqualFunc
    {
    public:
        bool operator()(const std::type_info* lhs_, const std::type_info* rhs_) const
        {
            return *lhs_ == *rhs_;
        }
    };

    static std::unordered_map<const std::type_info*, std::shared_ptr<void>, HashFunc, EqualFunc> m_instances;
    static std::mutex m_mutex;
};


template <typename T>
T* Handleton::GetInstance()
{

    static std::once_flag flag;
    std::call_once(flag, []
    {
        // lock m_mutex
        if (!m_instances.contains(&typeid(T)))
        {
            m_instances.emplace(&typeid(T), new T);
        }
    });

    return static_cast<T*>(m_instances.at(&typeid(T)).get());
}
}



#endif // ILRD_RD1645_HANDLETON_HPP
