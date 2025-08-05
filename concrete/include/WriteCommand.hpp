
//
// Created by bender on 4/7/25.
#ifndef  ILRD_RD1645_WRITECOMMAND_HPP
#define  ILRD_RD1645_WRITECOMMAND_HPP

#include "ICommand.hpp"


namespace ilrd
{

class WriteCommand final : public ICommand
{
public:
    WriteCommand() = default;
    ~WriteCommand() override = default;

    std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
        Run(std::shared_ptr<ITaskArgs> args_) override;

    WriteCommand(const WriteCommand& other_) = delete;
    WriteCommand& operator=(const WriteCommand& other_) = delete;
    WriteCommand(WriteCommand&& other_) = delete;
    WriteCommand& operator=(WriteCommand&& other_) = delete;
private:

};
}

#endif // ILRD_RD1645_WRITECOMMAND_HPP
