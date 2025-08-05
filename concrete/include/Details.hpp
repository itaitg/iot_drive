
#ifndef  ILRD_RD1645_DETAILS_HPP
#define  ILRD_RD1645_DETAILS_HPP

#include <memory>

#include "UID.hpp"

namespace ilrd
{

enum CLASS_TYPE : uint32_t
{
    READ_RESPONSE,
    WRITE_RESPONSE,
    READ_SEND,
    WRITE_SEND
};


struct TaskResult
{
    bool m_status;
    UID m_id;
    size_t m_sizeArr;
    std::shared_ptr<char[]> m_arr;
};
}


#endif // ILRD_RD1645_DETAILS_HPP
