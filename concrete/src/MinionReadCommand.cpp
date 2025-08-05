//
// Created by bender on 4/20/25.
// Approved by:

#include "MinionReadCommand.hpp"

#include "FileManager.hpp"
#include "Handleton.hpp"
#include "MasterProxy.hpp"
#include "MinionReadArgs.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations


std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>> ilrd
::MinionReadCommand::Run(std::shared_ptr<ITaskArgs> args_)
{
    auto read_args = static_cast<MinionReadArgs*>(args_.get());
    size_t offset = read_args->GetOffset();
    size_t length = read_args->GetLength();
    bool status  = true;

    std::shared_ptr<char[]> buffer(new char[length]);

    try
    {
        status = Handleton::GetInstance<FileManager>()->Read(offset, length, buffer.get());
    }
    catch(...)
    {
        Handleton::GetInstance<MasterProxy>()->SendReadResponse(false,
        read_args->GetUID(), read_args->GetLength());
    }
    Handleton::GetInstance<MasterProxy>()->SendReadResponse(status,
            read_args->GetUID(), read_args->GetLength(), buffer.get());

    return {};
}
