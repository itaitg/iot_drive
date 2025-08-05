
//
// Created by bender on 4/7/25.
#ifndef  ILRD_RD1645_READCOMMAND_HPP
#define  ILRD_RD1645_READCOMMAND_HPP

#include "ICommand.hpp"
#include "NBDReadArgs.hpp"

namespace ilrd
{

class ReadCommand final : public ICommand
{
public:
    ReadCommand() = default;
    ~ReadCommand() override = default;

    std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
        Run(std::shared_ptr<ITaskArgs> args_) override;

    ReadCommand(const ReadCommand& other_) = delete;
    ReadCommand& operator=(const ReadCommand& other_) = delete;
    ReadCommand(ReadCommand&& other_) = delete;
    ReadCommand& operator=(ReadCommand&& other_) = delete;

private:

};
}

#endif // ILRD_RD1645_READCOMMAND_HPP
