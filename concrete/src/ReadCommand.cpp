//
// Created by bender on 4/6/25.
// Approved by:

#include "ReadCommand.hpp"
#include "Handleton.hpp"
#include "MinionManager.hpp"
#include "ResponseManager.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>> ilrd
::ReadCommand::Run(const std::shared_ptr<ITaskArgs> args_)
{
    const auto args = dynamic_cast<NBDReadArgs*>(args_.get());

    Handleton::GetInstance<MinionManager>()->AddReadTask(args->GetOffset(),
        args->GetLength(), args->GetUID());

    int counter = 0;

    return std::make_pair([id = args->GetUID(), &counter]
    {
        if(++counter == 10)
        {
            if(Handleton::GetInstance<ResponseManager>()->Contains(id))
            {
                Handleton::GetInstance<ResponseManager>()->SendFail(id);

                return true;
            }
        }

        return false;

    }, std::chrono::milliseconds(100));
}


