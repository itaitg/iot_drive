//
// Created by bender on 4/20/25.
// Approved by:

#include "MinionWriteCommand.hpp"
#include "FileManager.hpp"
#include "MinionWriteArgs.hpp"
#include "MasterProxy.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations



std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>> ilrd
::MinionWriteCommand::Run(std::shared_ptr<ITaskArgs> args_)
{
    auto write_args = static_cast<MinionWriteArgs*>(args_.get());
    size_t offset = write_args->GetOffset();
    size_t length = write_args->GetLength();
    auto buffer = write_args->GetBuffer();
    bool status  = true;

    try
    {
        status = Handleton::GetInstance<FileManager>()->Write(offset, length, buffer.get());
    }
    catch(...)
    {
        Handleton::GetInstance<MasterProxy>()->SendWriteResponse(false, write_args->GetUID());
    }
    Handleton::GetInstance<MasterProxy>()->SendWriteResponse(status, write_args->GetUID());

    return {};
}
