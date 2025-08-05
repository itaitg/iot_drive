//
// Created by bender on 4/9/25.
// Approved by:


#include "ReadMessageSend.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::ReadMessageSend::ReadMessageSend(const size_t& offset_,
const size_t& length_, const UID& id_):
    AMessage(id_), m_offset(offset_), m_length(length_)
{}

ilrd::ReadMessageSend::ReadMessageSend(): AMessage(UID(0)), m_offset(0)
    , m_length(0)
{}

ilrd::CLASS_TYPE ilrd::ReadMessageSend::GetClassType()
{
    return READ_SEND;
}

char* ilrd::ReadMessageSend::ToBuffer(char* buffer_)
{
    buffer_ = AMessage::ToBuffer(buffer_);

    *reinterpret_cast<uint32_t*>(buffer_) = m_offset;
    buffer_ += sizeof(uint32_t);

    *reinterpret_cast<uint32_t*>(buffer_) = m_length;
    buffer_ += sizeof(uint32_t);

    return buffer_;
}


char* ilrd::ReadMessageSend::FromBuffer(char* buffer_)
{
    buffer_ = AMessage::FromBuffer(buffer_);

    m_offset = *reinterpret_cast<uint32_t*>(buffer_);
    buffer_ += sizeof(uint32_t);

    m_length = *reinterpret_cast<uint32_t*>(buffer_);
    buffer_ += sizeof(uint32_t);

    return buffer_;

}

uint32_t ilrd::ReadMessageSend::GetSize()
{
    return AMessage::GetSize() + sizeof(m_offset) + sizeof(m_length);
}

uint32_t ilrd::ReadMessageSend::GetOffset() const
{
    return m_offset;
}

uint32_t ilrd::ReadMessageSend::GetLength() const
{
    return m_length;
}
