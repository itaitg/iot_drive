//
// Created by bender on 4/7/25.
// Approved by:

#include "AMessage.hpp"
#include "Handleton.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations


ilrd::AMessage::AMessage(const UID& id_): m_id(id_)
{}

char* ilrd::AMessage::ToBuffer(char* buffer_)
{
    *reinterpret_cast<uint32_t*>(buffer_) = GetSize();
    buffer_ += sizeof(uint32_t);

    *reinterpret_cast<CLASS_TYPE*>(buffer_) = GetClassType();
    buffer_ += sizeof(CLASS_TYPE);

    *reinterpret_cast<UID*>(buffer_) = m_id;
    buffer_ += sizeof(UID);

    return buffer_;
}

char* ilrd::AMessage::FromBuffer(char* buffer_)
{
    m_id = *reinterpret_cast<UID*>(buffer_);
    buffer_ += sizeof(m_id);

    return buffer_;
}

uint32_t ilrd::AMessage::GetSize()
{
    return sizeof(m_id) + sizeof(uint32_t) + sizeof(uint32_t);
}

ilrd::UID& ilrd::AMessage::GetUID()
{
    return m_id;
}
