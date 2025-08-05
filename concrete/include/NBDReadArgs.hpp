
//
// Created by bender on 4/6/25.
#ifndef  ILRD_RD1645_NBDREADARGS_HPP
#define  ILRD_RD1645_NBDREADARGS_HPP


#include "ATaskArgs.hpp"

#include "NBDProxy.hpp"

namespace ilrd
{

class NBDReadArgs final : public ATaskArgs
{
public:
    explicit NBDReadArgs(const NBDArgs& args_);
    ~NBDReadArgs() override = default;

    size_t GetOffset() const;
    size_t GetLength() const;
    int GetKey() override;

    NBDReadArgs(const NBDReadArgs& other_) = delete;
    NBDReadArgs& operator=(const NBDReadArgs& other_) = delete;
    NBDReadArgs(ITaskArgs&& other_) = delete;
    NBDReadArgs& operator=(NBDReadArgs&& other_) = delete;

private:
    size_t m_offset;
    size_t m_length;
};
}

#endif // ILRD_RD1645_NBDREADARGS_HPP
