
//
// Created by bender on 4/20/25.
#ifndef  ILRD_RD1645_MINIONWRITECOMMAND_HPP
#define  ILRD_RD1645_MINIONWRITECOMMAND_HPP


#include "ICommand.hpp"


namespace ilrd
{

class MinionWriteCommand final : public ICommand
{
public:
    MinionWriteCommand() = default;
    ~MinionWriteCommand() override = default;

    std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
        Run(std::shared_ptr<ITaskArgs> args_) override;

    MinionWriteCommand(const MinionWriteCommand& other_) = delete;
    MinionWriteCommand& operator=(const MinionWriteCommand& other_) = delete;
    MinionWriteCommand(MinionWriteCommand&& other_) = delete;
    MinionWriteCommand& operator=(MinionWriteCommand&& other_) = delete;
private:

};
}

#endif // ILRD_RD1645_MINIONWRITECOMMAND_HPP
