//
// Created by bender on 4/6/25.
// Approved by:

#include "ResponseManager.hpp"

#include "Factory.hpp"
#include "ReadResponse.hpp"
#include "WriteResponse.hpp"
#include "Handleton.hpp"
#include "Logger.hpp"
#include "MinionManager.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations

void ilrd::ResponseManager::Init(NBDProxy& proxy_)
{
    Handleton::GetInstance<Logger>()->Log("ResponseManager initialized", Logger::DEBUG);
    proxy_.RegisterForNewTaskArgs(m_OnNewTask);
    Handleton::GetInstance<Factory<int, IResponse>>()->Register(0,
     [](){return std::make_shared<ReadResponse>();});
    Handleton::GetInstance<Factory<int, IResponse>>()->Register(1,
    [](){return std::make_shared<WriteResponse>();});
    m_nbd = &proxy_;
}

bool ilrd::ResponseManager::Contains(UID id_)
{
    return m_requests.contains(id_);
}

void ilrd::ResponseManager::SendFail(const UID& id_) const
{
    m_nbd->Reply(id_, false, 0 , nullptr);
}

ilrd::ResponseManager::ResponseManager(): m_ticketDoneCallback
                                          (*this, &ResponseManager::OnTicketDone), m_newTicketCallback(*this,
                                              &ResponseManager::OnTicketCreate), m_OnNewTask(*this, &ResponseManager::OnNewTask)
{
    Handleton::GetInstance<MinionManager>()->RegisterForNewTickets(&m_newTicketCallback);
}

void ilrd::ResponseManager::OnTicketDone(const std::shared_ptr<TaskResult>& results_)
{
    std::unique_lock lock(m_mutex);
    if(results_->m_status)
    {
        m_requests[results_->m_id]->OnSuccess(*m_nbd, *results_);
    }
    else
    {
        m_requests[results_->m_id]->OnFailure(*m_nbd, *results_);
    }
    m_requests.erase(results_->m_id);
}

void ilrd::ResponseManager::OnTicketCreate(const std::pair<UID&,
    std::shared_ptr<Ticket>&> uid_ticket_)
{
    Handleton::GetInstance<Logger>()->Log("Ticket created", Logger::DEBUG);
    uid_ticket_.second->RegisterToResultDispatcher(&m_ticketDoneCallback);
}

void ilrd::ResponseManager::OnNewTask(const std::shared_ptr<ATaskArgs>& args_)
{
    Handleton::GetInstance<Logger>()->Log("NewTask", Logger::DEBUG);
    std::unique_lock lock(m_mutex);
    m_requests.emplace(args_->GetUID(),  Handleton::GetInstance<Factory<int, IResponse>>()
        ->Create(args_->GetKey()));
}


