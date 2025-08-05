
//
// Created by bender on 4/9/25.
#ifndef  ILRD_RD1645_WRITEMESSAGERESPONSE_HPP
#define  ILRD_RD1645_WRITEMESSAGERESPONSE_HPP

#include "AMessageResponse.hpp"

namespace ilrd
{

class WriteMessageResponse final: public AMessageResponse
{
public:
    WriteMessageResponse(const bool& status_, UID& id_);
    WriteMessageResponse();
    ~WriteMessageResponse() override = default;

    CLASS_TYPE GetClassType() override;
    char* ToBuffer(char* buffer_) override;
    char* FromBuffer(char* buffer_) override;
    uint32_t GetSize() override;
    bool GetStatus() override;

    WriteMessageResponse(const WriteMessageResponse& other_) = delete;
    WriteMessageResponse& operator=(const WriteMessageResponse& other_) = delete;
    WriteMessageResponse(WriteMessageResponse&& other_) = delete;
    WriteMessageResponse& operator=(WriteMessageResponse&& other_) = delete;
private:


};
}

#endif // ILRD_RD1645_WRITEMESSAGERESPONSE_HPP
