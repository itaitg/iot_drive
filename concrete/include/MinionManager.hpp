
//
// Created by bender on 4/6/25.
#ifndef  ILRD_RD1645_MINIONMANAGER_HPP
#define  ILRD_RD1645_MINIONMANAGER_HPP


#include <thread>

#include "Handleton.hpp"
#include "Dispatcher.hpp"
#include "Reactor.hpp"
#include "UID.hpp"
#include "IMinionProxy.hpp"
#include "Ticket.hpp"
#include "ICommand.hpp"
#include "ATaskArgs.hpp"

namespace ilrd
{

class MinionManager
{
public:
    friend class Handleton;
    ~MinionManager() = default;

    void AddReadTask(size_t offset_, size_t length_, UID id_);
    void AddWriteTask(size_t offset_, size_t length_, UID id_,
        const std::shared_ptr<const char[]>& str_);

    void RegisterForNewTickets(ACallback<std::pair<UID&,
        std::shared_ptr<Ticket>&>>* callback_);
    void Init(size_t size_, const std::vector<std::shared_ptr<IMinionProxy>>& minions_);

    MinionManager(const MinionManager& other_) = delete;
    MinionManager& operator=(const MinionManager& other_) = delete;
    MinionManager(MinionManager&& other_) = delete;
    MinionManager& operator=(MinionManager&& other_) = delete;
private:
    MinionManager();
    std::vector<std::shared_ptr<IMinionProxy>> m_minions;
    Dispatcher<std::pair<UID&, std::shared_ptr<Ticket>&>> m_dispatcherNewTicket;
    //std::map<UID, std::shared_ptr<Ticket>> m_tickets;
    std::mutex m_mutex;
    Reactor m_reactor;
    std::jthread m_thread;
    size_t m_minion_size;
};
}

#endif // ILRD_RD1645_MINIONMANAGER_HPP
