
//
// Created by bender on 4/7/25.
#ifndef  ILRD_RD1645_UID_HPP
#define  ILRD_RD1645_UID_HPP

#include <atomic>

namespace ilrd
{

class UID 
{
public:
    UID();
    explicit UID(size_t dummy_);
    ~UID() = default;

    bool operator==(const UID& other_) const;
    bool operator<(const UID& other_) const;
    UID& operator=(const UID& other_) = default;
    [[nodiscard]] size_t GetUID() const;
    UID(const UID& other_) = default;

    UID(UID&& other_) = delete;
    UID& operator=(UID&& other_) = delete;
private:
    static std::atomic<size_t> m_counter;
    size_t m_uid;
};
}

#endif // ILRD_RD1645_UID_HPP
