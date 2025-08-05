
//
// Created by bender on 4/7/25.
#ifndef  ILRD_RD1645_TICKET_HPP
#define  ILRD_RD1645_TICKET_HPP

#include <memory>

#include "Dispatcher.hpp"
#include "IMinionProxy.hpp"
#include "Details.hpp"

namespace ilrd
{


class Ticket
{
public:
    explicit Ticket(UID& id_);
    ~Ticket() = default;

    void OnProxyDone(const std::shared_ptr<TaskResult>& results_);
    void RegisterToResultDispatcher(ACallback<const std::shared_ptr<TaskResult>&>* callback_);

    Ticket(const Ticket& other_) = delete;
    Ticket& operator=(const Ticket& other_) = delete;
    Ticket(Ticket&& other_) = delete;
    Ticket& operator=(Ticket&& other_) = delete;

private:
    Dispatcher<const std::shared_ptr<TaskResult>&> m_dispatcher;
    std::vector<std::shared_ptr<IMinionProxy>> m_proxies;
    const UID& m_id;
    size_t m_counter;

};
}

#endif // ILRD_RD1645_TICKET_HPP
