
//
// Created by bender on 4/7/25.
#ifndef  ILRD_RD1645_ATASKARGS_HPP
#define  ILRD_RD1645_ATASKARGS_HPP


#include "ITaskArgs.hpp"
#include "UID.hpp"

namespace ilrd
{

class ATaskArgs : public ITaskArgs
{
public:
    ATaskArgs() = default;
    ~ATaskArgs() override = default;

    UID& GetUID();
    void SetUID(UID id_);

    ATaskArgs(const ATaskArgs& other_) = delete;
    ATaskArgs& operator=(const ATaskArgs& other_) = delete;
    ATaskArgs(ATaskArgs&& other_) = delete;
    ATaskArgs& operator=(ATaskArgs&& other_) = delete;
private:
    UID m_uid;

};


}

#endif // ILRD_RD1645_ATASKARGS_HPP
