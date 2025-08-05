
//
// Created by bender on 3/27/25.
#ifndef  ILRD_RD1645_ICOMMAND_HPP
#define  ILRD_RD1645_ICOMMAND_HPP

#include <optional>

#include "ASyncInjection.hpp"
#include "ATaskArgs.hpp"

namespace ilrd
{
///
///command to be run by the @FW_Task (must be inherited)
class ICommand 
{
public:
    /// the function to run, logic needs to be implemnted
    /// @param args_ from @ITaskArgs
    /// @return return (function for @AsyncInjection) return "{}" to run only once
    virtual std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
        Run(std::shared_ptr<ITaskArgs> args_) = 0;

    virtual ~ICommand() = default;
    ICommand() = default;
    ICommand(const ICommand& other_) = delete;
    ICommand& operator=(const ICommand& other_) = delete;
    ICommand(ICommand&& other_) = delete;
    ICommand& operator=(ICommand&& other_) = delete;
};
}

#endif // ILRD_RD1645_ICOMMAND_HPP
