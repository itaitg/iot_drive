//
// Created by bender on 4/7/25.
// Approved by:


#include "WriteCommand.hpp"
#include "Handleton.hpp"
#include "MinionManager.hpp"
#include "NBDWriteArgs.hpp"
#include "ResponseManager.hpp"


//////////////////include

//////////////////static declarations

//////////////////constructors

namespace ilrd
{
class ResponseManager;
}

//////////////////static implementations
std::optional<std::pair<std::function<bool()>, std::chrono::milliseconds>>
        ilrd::WriteCommand::Run(std::shared_ptr<ITaskArgs> args_)
{
    auto& args = static_cast<NBDWriteArgs&>(*args_.get());

    Handleton::GetInstance<MinionManager>()->AddWriteTask(args.GetOffset(),
    args.GetLength(), args.GetUID(), args.GetBuffer());

    int counter = 0;

    return std::make_pair([id = args.GetUID(), &counter]
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
