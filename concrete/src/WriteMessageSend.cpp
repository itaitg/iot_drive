//
// Created by bender on 4/9/25.
// Approved by:

#include "WriteMessageSend.hpp"

#include <cstring>

//////////////////include

//////////////////static declarations

//////////////////constructors

static char* StrInit(const char* str_, size_t length_)
{
    const auto buffer = new char[length_];
    memcpy(buffer, str_, length_);
    return buffer;
}

//////////////////static implementations
ilrd::WriteMessageSend::WriteMessageSend(const size_t& offset_,
    const size_t& length_, const char* str_, const UID& id_):
        AMessage(id_), m_offset(offset_), m_length(length_),
        m_str(StrInit(str_, length_))
{}

ilrd::WriteMessageSend::WriteMessageSend(): AMessage(UID(1)), m_offset(0),
    m_length(0), m_str(nullptr)
{
}

ilrd::WriteMessageSend::~WriteMessageSend()
{
    delete[] m_str;
}

ilrd::CLASS_TYPE ilrd::WriteMessageSend::GetClassType()
{
    return WRITE_SEND;
}

char* ilrd::WriteMessageSend::ToBuffer(char* buffer_)
{
    buffer_ = AMessage::ToBuffer(buffer_);

    *reinterpret_cast<uint32_t*>(buffer_) = m_offset;
    buffer_ += sizeof(uint32_t);

    *reinterpret_cast<uint32_t*>(buffer_) = m_length;
    buffer_ += sizeof(uint32_t);

    memcpy(buffer_, m_str, m_length);
    buffer_ += m_length;

    return buffer_;
}

char* ilrd::WriteMessageSend::FromBuffer(char* buffer_)
{
    buffer_ = AMessage::FromBuffer(buffer_);

    m_offset = *reinterpret_cast<uint32_t*>(buffer_);
    buffer_ += sizeof(uint32_t);

    m_length = *reinterpret_cast<uint32_t*>(buffer_);
    buffer_ += sizeof(uint32_t);

    const auto temp_buffer = new char[m_length];
    memcpy(temp_buffer, buffer_, m_length);
    buffer_ += m_length;
    // delete[] m_str;
    m_str = temp_buffer;

    return buffer_;
}

uint32_t ilrd::WriteMessageSend::GetSize()
{
    return AMessage::GetSize() + sizeof(m_offset) + m_length + sizeof(m_length);
}

uint32_t ilrd::WriteMessageSend::GetOffset() const
{
    return m_offset;
}

uint32_t ilrd::WriteMessageSend::GetLength() const
{
    return m_length;
}

char* ilrd::WriteMessageSend::GetStr()
{
    return m_str;
}
