//
// Created by bender on 4/6/25.
// Approved by:

#include "MinionManager.hpp"

#include <Factory.hpp>
#include <thread>

#include "ReadMessageResponse.hpp"
#include "ReadMessageSend.hpp"
#include "WriteMessageResponse.hpp"
#include "Ticket.hpp"
#include "Details.hpp"

ilrd::MinionManager::MinionManager(): m_thread(), m_minion_size()
{}

void ilrd::MinionManager::AddReadTask(size_t offset_, size_t length_, UID id_)
{
    auto ticket = std::make_shared<Ticket>(id_);
    std::unique_lock lock(m_mutex);
    m_dispatcherNewTicket.Notify({id_, ticket});
    lock.unlock();
    size_t minion_ind = offset_ / m_minion_size;
    size_t offset = offset_ % m_minion_size;

    m_minions[minion_ind]->SendReadTask(offset, length_, id_,
        [ticket](const std::shared_ptr<TaskResult>&
        results_) {ticket->OnProxyDone(results_);});
    //
    // minion_ind = (minion_ind + 1) % m_minions.size();
    // offset = offset + m_minion_size;

    // ticket->AddMinion(m_minions[minion_ind]);
    // m_minions[minion_ind]->SendReadTask(offset, length_, id_,
    //     [ticket](const std::shared_ptr<TaskResult>&
    //     results_) {ticket->OnProxyDone(results_);});
}

void ilrd::MinionManager::AddWriteTask(size_t offset_, size_t length_, UID id_,
    const std::shared_ptr<const char[]>& str_)
{
    auto ticket = std::make_shared<Ticket>(id_);
    m_dispatcherNewTicket.Notify({id_, ticket});

    size_t minion_ind = offset_ / m_minion_size;
    size_t offset = offset_ % m_minion_size;
    m_minions[minion_ind]->SendWriteTask(offset, length_ ,id_, str_,
        [ticket] (const std::shared_ptr<TaskResult>& results_)
        {ticket->OnProxyDone(results_);});

    // minion_ind = (minion_ind + 1) % m_minions.size();
    // offset = offset + m_minion_size;
    //
    // ticket->AddMinion(m_minions[minion_ind]);
    // m_minions[minion_ind]->SendWriteTask(offset, length_ ,id_, str_,
    //     [ticket] (const std::shared_ptr<TaskResult>& results_)
    //     {ticket->OnProxyDone(results_);});
}

void ilrd::MinionManager::RegisterForNewTickets(ACallback<std::pair<UID&,
        std::shared_ptr<Ticket>&>>* callback_)
{
    m_dispatcherNewTicket.Register(*callback_);
}

void ilrd::MinionManager::Init(const size_t size_, const std::vector<std::shared_ptr<IMinionProxy>>& minions_)
{
    m_minion_size = size_;

    Handleton::GetInstance<Factory<CLASS_TYPE, AMessageResponse>>()
        ->Register(READ_RESPONSE, [](){return std::make_shared<ReadMessageResponse>();});

    Handleton::GetInstance<Factory<CLASS_TYPE, AMessageResponse>>()
        ->Register(WRITE_RESPONSE, [](){return std::make_shared<WriteMessageResponse>();});

    m_minions = minions_;
     for(size_t i = 0; i < minions_.size(); ++i)
     {
         m_reactor.Register(m_minions[i]->GetMinionFD(), READ, [this, i](int, MODE)
         {
             m_minions[i]->OnMinionFDWakeUp();
         });
     }
         m_thread = std::jthread([this]{m_reactor.Run();});

}

