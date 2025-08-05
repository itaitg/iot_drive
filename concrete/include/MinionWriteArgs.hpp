
//
// Created by bender on 4/20/25.
#ifndef  ILRD_RD1645_MINIONWRITEARGS_HPP
#define  ILRD_RD1645_MINIONWRITEARGS_HPP

#include "ATaskArgs.hpp"
#include "MasterProxy.hpp"
namespace ilrd
{

class MinionWriteArgs: public ATaskArgs
{
public:
    explicit MinionWriteArgs(const MinionArgs& args_);
    ~MinionWriteArgs() override = default;


    size_t GetOffset() const;
    size_t GetLength() const;
    std::shared_ptr<const char[]> GetBuffer() const;
    int GetKey();

    MinionWriteArgs(const MinionWriteArgs& other_) = delete;
    MinionWriteArgs& operator=(const MinionWriteArgs& other_) = delete;
    MinionWriteArgs(MinionWriteArgs&& other_) = delete;
    MinionWriteArgs& operator=(MinionWriteArgs&& other_) = delete;

private:
    size_t m_offset;
    size_t m_length;
    std::shared_ptr<const char[]> m_buffer;
};
}

#endif // ILRD_RD1645_MINIONWRITEARGS_HPP
