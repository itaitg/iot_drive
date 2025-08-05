
//
// Created by bender on 4/9/25.
#ifndef  ILRD_RD1645_READMESSAGERESPONSE_HPP
#define  ILRD_RD1645_READMESSAGERESPONSE_HPP


#include <memory>

#include "AMessageResponse.hpp"

namespace ilrd
{

class ReadMessageResponse final : public AMessageResponse
{
public:
    explicit ReadMessageResponse(bool status_, const UID& id_,
        char* str_, size_t length_);
    explicit ReadMessageResponse();
    ~ReadMessageResponse() override = default;

    CLASS_TYPE GetClassType() override;
    char* ToBuffer(char* buffer_) override;
    char* FromBuffer(char* buffer_) override;
    uint32_t GetSize() override;
    uint32_t GetLengthMessage() const;
    bool GetStatus() override;
    std::shared_ptr<char[]> GetStr();

    ReadMessageResponse(const ReadMessageResponse& other_) = delete;
    ReadMessageResponse& operator=(const ReadMessageResponse& other_) = delete;
    ReadMessageResponse(ReadMessageResponse&& other_) = delete;
    ReadMessageResponse& operator=(ReadMessageResponse&& other_) = delete;
private:
    std::shared_ptr<char[]> m_str;
    uint32_t m_length;
};
}

#endif // ILRD_RD1645_AMESSAGERESPONSE_HPP
