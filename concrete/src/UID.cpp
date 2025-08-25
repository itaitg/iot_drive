
#include "UID.hpp"

std::atomic<size_t> ilrd::UID::m_counter = 1;

ilrd::UID::UID(): m_uid(m_counter++){}
ilrd::UID::UID(size_t dummy_): m_uid(0){(void)dummy_;}

bool ilrd::UID::operator==(const UID& other_) const
{
    return m_uid == other_.m_uid;
}

bool ilrd::UID::operator<(const UID& other_) const
{
    return m_uid < other_.m_uid;
}

size_t ilrd::UID::GetUID() const
{
    return m_uid;
}
