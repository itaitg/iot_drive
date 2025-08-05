
//
// Created by bender on 4/6/25.
#ifndef  ILRD_RD1645_RESPONSEMANAGER_HPP
#define  ILRD_RD1645_RESPONSEMANAGER_HPP


#include <map>

#include "IResponse.hpp"
#include "NBDProxy.hpp"
#include "Ticket.hpp"



namespace ilrd
{

class ResponseManager
{
public:
    friend class Handleton;
    void Init(NBDProxy& proxy_);
    ~ResponseManager() = default;
    bool Contains(UID id_);
    void SendFail(const UID& id_) const;

    ResponseManager(const ResponseManager& other_) = delete;
    ResponseManager& operator=(const ResponseManager& other_) = delete;
    ResponseManager(ResponseManager&& other_) = delete;
    ResponseManager& operator=(ResponseManager&& other_) = delete;
private:
    ResponseManager();
    NBDProxy* m_nbd;
    std::mutex m_mutex;

    std::map<UID, std::shared_ptr<IResponse>> m_requests;
    Callback<const std::shared_ptr<TaskResult>&, ResponseManager> m_ticketDoneCallback;
    Callback<std::pair<UID&, std::shared_ptr<Ticket>&>, ResponseManager>
        m_newTicketCallback;
    Callback<const std::shared_ptr<ATaskArgs>&, ResponseManager> m_OnNewTask;

    void OnTicketDone(const std::shared_ptr<TaskResult>& results_);
    void OnTicketCreate(const std::pair<UID&, std::shared_ptr<Ticket>&>);
    void OnNewTask(const std::shared_ptr<ATaskArgs>& args_);
};
}

#endif // ILRD_RD1645_RESPONSEMANAGER_HPP
