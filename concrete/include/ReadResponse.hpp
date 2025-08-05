
//
// Created by bender on 4/8/25.
#ifndef  ILRD_RD1645_READRESPONSE_HPP
#define  ILRD_RD1645_READRESPONSE_HPP

#include "IResponse.hpp"

namespace ilrd
{

class ReadResponse final : public IResponse
{
public:
    ReadResponse() = default;
    ~ReadResponse() override = default;

    void OnFailure(NBDProxy& proxy_, TaskResult& result_) override;
    void OnSuccess(NBDProxy& proxy_, TaskResult& result_) override;

    ReadResponse(const ReadResponse& other_) = delete;
    ReadResponse& operator=(const ReadResponse& other_) = delete;
    ReadResponse(ReadResponse&& other_) = delete;
    ReadResponse& operator=(ReadResponse&& other_) = delete;
private:

};
}

#endif // ILRD_RD1645_READRESPONSE_HPP
