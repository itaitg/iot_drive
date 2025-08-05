//
// Created by bender on 4/9/25.
// Approved by:

#include "ReadMessageResponse.hpp"

#include <cstring>

//////////////////include

//////////////////static declarations

//////////////////constructors
//////////////////static implementations

static char* StrInit(const char* str_, size_t length_)
{
    const auto buffer = new char[length_];
    memcpy(buffer, str_, length_);
    return buffer;
}

ilrd::ReadMessageResponse::ReadMessageResponse(bool status_, const UID&
    id_, char* str_, size_t length_): AMessageResponse(status_, id_),
    m_str(StrInit(str_, length_)), m_length(length_)
{}

ilrd::ReadMessageResponse::ReadMessageResponse(): AMessageResponse(false, UID
(1)), m_str(nullptr), m_length(0)
{}



ilrd::CLASS_TYPE ilrd::ReadMessageResponse::GetClassType()
{
    return READ_RESPONSE;
}

char* ilrd::ReadMessageResponse::ToBuffer(char* buffer_)
{
    buffer_ = AMessageResponse::ToBuffer(buffer_);

    *reinterpret_cast<uint32_t*>(buffer_) = m_length;
    buffer_ += sizeof(uint32_t);

    memcpy(buffer_, m_str.get(), m_length);
    buffer_ += m_length;

    return buffer_;
}

char* ilrd::ReadMessageResponse::FromBuffer(char* buffer_)
{
    buffer_ = AMessageResponse::FromBuffer(buffer_);

    m_length = *reinterpret_cast<uint32_t*>(buffer_);
    buffer_ += sizeof(uint32_t);

    auto buffer = std::make_shared<char[]>(m_length + 1);

    memcpy(buffer.get(), buffer_, m_length);
    *(buffer.get() + m_length) = '\0';
    buffer_ += m_length;
    m_str = buffer;

    return buffer_;
}

uint32_t ilrd::ReadMessageResponse::GetSize()
{
    return AMessageResponse::GetSize() + m_length + sizeof(m_length);
}

uint32_t ilrd::ReadMessageResponse::GetLengthMessage() const
{
    return m_length;
}

bool ilrd::ReadMessageResponse::GetStatus()
{
    return AMessageResponse::GetStatus();
}

std::shared_ptr<char[]> ilrd::ReadMessageResponse::GetStr()
{
    return m_str;
}
