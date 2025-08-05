//
// Created by bender on 4/8/25.
// Approved by:

#include "ReadResponse.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations

void ilrd::ReadResponse::OnFailure(NBDProxy& proxy_, TaskResult& result_)
{
    proxy_.Reply(result_.m_id, false, 0, nullptr);
}

void ilrd::ReadResponse::OnSuccess(NBDProxy& proxy_, TaskResult& result_)
{
    proxy_.Reply(result_.m_id, true, result_.m_sizeArr, result_.m_arr);
}
