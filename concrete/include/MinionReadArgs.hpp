
//
// Created by bender on 4/20/25.
#ifndef  ILRD_RD1645_MINIONREADARGS_HPP
#define  ILRD_RD1645_MINIONREADARGS_HPP


#include "ATaskArgs.hpp"
#include "MasterProxy.hpp"

namespace ilrd
{

class MinionReadArgs: public ATaskArgs
{
public:
    explicit MinionReadArgs(const MinionArgs& args_);
    ~MinionReadArgs() override = default;

    size_t GetOffset() const;
    size_t GetLength() const;
    int GetKey();

    MinionReadArgs(const MinionReadArgs& other_) = delete;
    MinionReadArgs& operator=(const MinionReadArgs& other_) = delete;
    MinionReadArgs(MinionReadArgs&& other_) = delete;
    MinionReadArgs& operator=(MinionReadArgs&& other_) = delete;

private:
    size_t m_offset;
    size_t m_length;
};
}

#endif // ILRD_RD1645_MINIONREADARGS_HPP
