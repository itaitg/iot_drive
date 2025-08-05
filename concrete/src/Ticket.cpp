//
// Created by bender on 4/7/25.
// Approved by:

#include "Ticket.hpp"
#include "Handleton.hpp"
#include "Logger.hpp"
#include "ReadMessageResponse.hpp"
#include "ResponseManager.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations


ilrd::Ticket::Ticket(UID& id_): m_id(id_), m_counter(2)
{}

void ilrd::Ticket::OnProxyDone(const std::shared_ptr<TaskResult>& results_)
{
    if(results_->m_status)
    {
        m_dispatcher.Notify(results_);
    }
    if(--m_counter == 0)
    {
        Handleton::GetInstance<Logger>()->Log("Ticket Closed", Logger::DEBUG);
        m_counter = 2;
    }
}
void ilrd::Ticket::RegisterToResultDispatcher(ACallback<const std::shared_ptr<TaskResult>&>*
    callback_)
{
    Handleton::GetInstance<Logger>()->Log("Registered to Ticket", Logger::DEBUG);
    m_dispatcher.Register(*callback_);
}
