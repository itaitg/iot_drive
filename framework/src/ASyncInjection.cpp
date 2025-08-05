//
// Created by bender on 3/26/25.
// Approved by:Idan


//////////////////include

#include "ASyncInjection.hpp"
#include "Handleton.hpp"
#include "Scheduler.hpp"


///////////////////////ASyncInjection

ilrd::ASyncInjection::ASyncInjection(const std::function<bool()>& func_,
    const std::chrono::milliseconds& interval_): m_Func(func_), m_interval
    (interval_), m_task(std::make_shared<ASyncInjectionTask>(*this))
{
    Handleton::GetInstance<Scheduler>()->AddTask(m_task, m_interval);
}


void ilrd::ASyncInjection::PerformAction()
{
    if(m_Func())
    {
        Handleton::GetInstance<Scheduler>()->AddTask(m_task, m_interval);
    }
    else
    {
        delete this;
    }
}


///////////////////////ASyncInjectionTask

ilrd::ASyncInjection::ASyncInjectionTask::ASyncInjectionTask(ASyncInjection&
task_): m_task(task_)
{}

void ilrd::ASyncInjection::ASyncInjectionTask::Run()
{
    m_task.PerformAction();
}
