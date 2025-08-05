
//
// Created by bender on 4/6/25.
#ifndef  ILRD_RD1645_MINIONPROXY_HPP
#define  ILRD_RD1645_MINIONPROXY_HPP

#include <functional>
#include <map>

#include "UDP_socket.hpp"
#include "IMinionProxy.hpp"

namespace ilrd
{

class MinionProxy final : public IMinionProxy
{
public:
    MinionProxy(const char* port_, const char* ip_);
    ~MinionProxy() override = default;

    void SendWriteTask(size_t offset_, size_t length_, UID& id_,
            const std::shared_ptr<const char[]>& data_, const
            std::function<void(const std::shared_ptr<TaskResult>&)>&
            OnDone) override;
    void SendReadTask(size_t offset_, size_t length_, UID& id_,
             const std::function<void (const std::shared_ptr<TaskResult>&)>&
             OnDone) override;
    int GetMinionFD() override;
    void OnMinionFDWakeUp() override;

    MinionProxy(const MinionProxy& other_) = delete;
    MinionProxy& operator=(const MinionProxy& other_) = delete;
    MinionProxy(MinionProxy&& other_) = delete;
    MinionProxy& operator=(MinionProxy&& other_) = delete;

private:
    UDP_Socket m_socket;
    std::mutex m_mutex;
    std::map<UID, std::function<void(const std::shared_ptr<TaskResult>&)>> m_map;
};

}


#endif // ILRD_RD1645_MINIONPROXY_HPP
