
//
// Created by bender on 4/8/25.
#ifndef  ILRD_RD1645_IRESPONSE_HPP
#define  ILRD_RD1645_IRESPONSE_HPP

#include "NBDProxy.hpp"
#include "Ticket.hpp"


namespace ilrd
{


class IResponse 
{
public:
    IResponse() = default;
    virtual ~IResponse() = default;

    virtual void OnSuccess(NBDProxy& proxy_, TaskResult& result_) = 0;
    virtual void OnFailure(NBDProxy& proxy_, TaskResult& result_) = 0;

    IResponse(const IResponse& other_) = delete;
    IResponse& operator=(const IResponse& other_) = delete;
    IResponse(IResponse&& other_) = delete;
    IResponse& operator=(IResponse&& other_) = delete;
};
}

#endif // ILRD_RD1645_IRESPONSE_HPP
