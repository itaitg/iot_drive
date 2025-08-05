
//
// Created by bender on 4/6/25.
#ifndef  ILRD_RD1645_NBDWRITEARGS_HPP
#define  ILRD_RD1645_NBDWRITEARGS_HPP

#include "ATaskArgs.hpp"
#include "NBDProxy.hpp"

namespace ilrd
{

class NBDWriteArgs final : public ATaskArgs
{
public:
    explicit NBDWriteArgs(const NBDArgs& args_);
    ~NBDWriteArgs() override = default;

    size_t GetOffset() const;
    size_t GetLength() const;
    std::shared_ptr<const char[]> GetBuffer() const;
    int GetKey() override;

    NBDWriteArgs(const NBDWriteArgs& other_) = delete;
    NBDWriteArgs& operator=(const NBDWriteArgs& other_) = delete;
    NBDWriteArgs(ITaskArgs&& other_) = delete;
    NBDWriteArgs& operator=(NBDWriteArgs&& other_) = delete;

private:
    size_t m_offset;
    size_t m_length;
    std::shared_ptr<const char[]> m_buffer;

};
}

#endif // ILRD_RD1645_NBDWRITEARGS_HPP
