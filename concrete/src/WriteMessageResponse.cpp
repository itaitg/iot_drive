//
// Created by bender on 4/9/25.
// Approved by:

#include "WriteMessageResponse.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::WriteMessageResponse::WriteMessageResponse(const bool& status_,
    UID& id_): AMessageResponse(status_, id_)
{}

ilrd::WriteMessageResponse::WriteMessageResponse(): AMessageResponse(false, UID(0))

{
}

ilrd::CLASS_TYPE ilrd::WriteMessageResponse::GetClassType()
{
    return WRITE_RESPONSE;
}

char* ilrd::WriteMessageResponse::ToBuffer(char* buffer_)
{
    buffer_ = AMessageResponse::ToBuffer(buffer_);

    return buffer_;
}

char* ilrd::WriteMessageResponse::FromBuffer(char* buffer_)
{
    buffer_ = AMessageResponse::FromBuffer(buffer_);

    return buffer_;
}

uint32_t ilrd::WriteMessageResponse::GetSize()
{
    return AMessageResponse::GetSize();
}

bool ilrd::WriteMessageResponse::GetStatus()
{
    return AMessageResponse::GetStatus();
}

