
//
// Created by bender on 4/10/25.

#ifndef  ILRD_RD1645_AMESSAGERESPONSE_HPP
#define  ILRD_RD1645_AMESSAGERESPONSE_HPP


#include "AMessage.hpp"

namespace ilrd
{

class AMessageResponse: public AMessage
{
public:
    AMessageResponse(bool status_, const UID& id_);
    ~AMessageResponse() override = default;

    CLASS_TYPE GetClassType() override = 0;
    char* ToBuffer(char* buffer_) override;
    char* FromBuffer(char* buffer_) override;
    uint32_t GetSize() override;
    virtual bool GetStatus();


    AMessageResponse(const AMessageResponse& other_) = delete;
    AMessageResponse& operator=(const AMessageResponse& other_) = delete;
    AMessageResponse(AMessageResponse&& other_) = delete;
    AMessageResponse& operator=(AMessageResponse&& other_) = delete;

private:
    bool m_status;
};
}

#endif // ILRD_RD1645_AMESSAGERESPONSE_HPP
