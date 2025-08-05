//
// Created by bender on 3/27/25.
// Approved by:


//////////////////include


#include "ASyncInjection.hpp"
#include "FW_TPTask.hpp"
#include "Factory.hpp"
#include "Handleton.hpp"
#include "ICommand.hpp"
#include "Logger.hpp"

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::FW_TPTask::FW_TPTask(const std::shared_ptr<ITaskArgs>& task_args_):
m_args(task_args_){}

void ilrd::FW_TPTask::Run()
{
    std::shared_ptr<ICommand> p_command;
    try
    {
        p_command = Handleton::GetInstance<Factory<int, ICommand>>()->Create(m_args->GetKey());
    }
    catch(...)
    {
        Handleton::GetInstance<Logger>()->Log(
            "doesn't exist",
        Logger::SEVERITY::WARNING);
    }
    const auto run_again = p_command->Run(m_args);

    if(run_again)
    {
        new ASyncInjection(run_again->first, run_again->second);
    }
}
