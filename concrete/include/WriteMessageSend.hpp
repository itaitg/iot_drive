
//
// Created by bender on 4/9/25.
#ifndef  ILRD_RD1645_WRITEMESSAGESEND_HPP
#define  ILRD_RD1645_WRITEMESSAGESEND_HPP

#include "AMessage.hpp"

namespace ilrd
{

class WriteMessageSend final : public AMessage
{
public:
    WriteMessageSend(const size_t& offset_, const size_t& length_, const char*
            str_, const UID& id_);
    WriteMessageSend();
    ~WriteMessageSend() override;

    CLASS_TYPE GetClassType() override;
    char* ToBuffer(char* buffer_) override;
    char* FromBuffer(char* buffer_) override;
    uint32_t GetSize() override;
    uint32_t GetOffset() const;
    uint32_t GetLength() const;
    char* GetStr();

    WriteMessageSend(const WriteMessageSend& other_) = delete;
    WriteMessageSend& operator=(const WriteMessageSend& other_) = delete;
    WriteMessageSend(WriteMessageSend&& other_) = delete;
    WriteMessageSend& operator=(WriteMessageSend&& other_) = delete;
private:
    uint32_t m_offset;
    uint32_t m_length;
    char* m_str;
};
}

#endif // ILRD_RD1645_WRITEMESSAGESEND_HPP
