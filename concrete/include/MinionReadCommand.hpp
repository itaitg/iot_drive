
//
// Created by bender on 4/20/25.
#ifndef  ILRD_RD1645_MINIONREADCOMMAND_HPP
#define  ILRD_RD1645_MINIONREADCOMMAND_HPP

#include "ICommand.hpp"

namespace ilrd
{

class MinionReadCommand final : public ICommand
{
public:
    MinionReadCommand() = default;
    ~MinionReadCommand() override = default;

    std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
        Run(std::shared_ptr<ITaskArgs> args_) override;

    MinionReadCommand(const MinionReadCommand& other_) = delete;
    MinionReadCommand& operator=(const MinionReadCommand& other_) = delete;
    MinionReadCommand(MinionReadCommand&& other_) = delete;
    MinionReadCommand& operator=(MinionReadCommand&& other_) = delete;
};
}

#endif // ILRD_RD1645_MINIONREADCOMMAND_HPP
