
//
// Created by bender on 4/7/25.
#ifndef  ILRD_RD1645_AMESSAGE_HPP
#define  ILRD_RD1645_AMESSAGE_HPP

#include "Details.hpp"
#include "UID.hpp"

namespace ilrd
{



class AMessage 
{
public:
    explicit AMessage(const UID& id_);
    virtual ~AMessage() = default;

    virtual CLASS_TYPE GetClassType() = 0;
    virtual char* ToBuffer(char* buffer_);
    virtual char* FromBuffer(char* buffer_);
    virtual uint32_t GetSize() = 0;

    UID& GetUID();

    AMessage(const AMessage& other_) = delete;
    AMessage& operator=(const AMessage& other_) = delete;
    AMessage(AMessage&& other_) = delete;
    AMessage& operator=(AMessage&& other_) = delete;
private:
    UID m_id;

};
}

#endif // ILRD_RD1645_AMESSAGE_HPP
