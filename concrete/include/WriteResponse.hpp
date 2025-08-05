
//
// Created by bender on 4/8/25.
#ifndef  ILRD_RD1645_WRITERESPONSE_HPP
#define  ILRD_RD1645_WRITERESPONSE_HPP

#include "IResponse.hpp"

namespace ilrd
{

class WriteResponse final : public IResponse
{
public:
    WriteResponse() = default;
    ~WriteResponse() override = default;

    void OnFailure(NBDProxy& proxy_, TaskResult& result_) override;
    void OnSuccess(NBDProxy& proxy_, TaskResult& result_) override;

    WriteResponse(const WriteResponse& other_) = delete;
    WriteResponse& operator=(const WriteResponse& other_) = delete;
    WriteResponse(WriteResponse&& other_) = delete;
    WriteResponse& operator=(WriteResponse&& other_) = delete;
private:

};
}

#endif // ILRD_RD1645_WRITERESPONSE_HPP
