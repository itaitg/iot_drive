
//
// Created by bender on 4/9/25.
#ifndef  ILRD_RD1645_READMESSAGESEND_HPP
#define  ILRD_RD1645_READMESSAGESEND_HPP

#include "AMessage.hpp"

namespace ilrd
{

class ReadMessageSend final : public AMessage
{
public:
    ReadMessageSend(const size_t& offset_, const size_t& length_, const UID& id_);
    ReadMessageSend();
    ~ReadMessageSend() override = default;

    CLASS_TYPE GetClassType() override;
    char* ToBuffer(char* buffer_) override;
    char* FromBuffer(char* buffer_) override;
    uint32_t GetSize() override;
    uint32_t GetOffset() const;
    uint32_t GetLength() const;


    ReadMessageSend(const ReadMessageSend& other_) = delete;
    ReadMessageSend& operator=(const ReadMessageSend& other_) = delete;
    ReadMessageSend(ReadMessageSend&& other_) = delete;
    ReadMessageSend& operator=(ReadMessageSend&& other_) = delete;

private:
    uint32_t m_offset;
    uint32_t m_length;
};
}

#endif // ILRD_RD1645_READMESSAGESEND_HPP
