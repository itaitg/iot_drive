
//
// Created by bender on 4/6/25.
#ifndef  ILRD_RD1645_IMINIONPROXY_HPP
#define  ILRD_RD1645_IMINIONPROXY_HPP

#include <functional>
#include <memory>

#include "Details.hpp"

#include "UID.hpp"

namespace ilrd
{

class IMinionProxy 
{
public:
    IMinionProxy() = default;
    virtual ~IMinionProxy() = default;

    virtual void SendWriteTask(size_t offset_, size_t length_, UID& id_,
            const std::shared_ptr<const char[]>& data_, const
            std::function<void(const std::shared_ptr<TaskResult>&)>&
            OnDone) = 0;
    virtual void SendReadTask(size_t offset_, size_t length_, UID& id_,
             const std::function<void(const std::shared_ptr<TaskResult>&)>&
              OnDone) = 0;
    virtual int GetMinionFD() = 0;
    virtual void OnMinionFDWakeUp() = 0;

    IMinionProxy(const IMinionProxy& other_) = delete;
    IMinionProxy& operator=(const IMinionProxy& other_) = delete;
    IMinionProxy(IMinionProxy&& other_) = delete;
    IMinionProxy& operator=(IMinionProxy&& other_) = delete;
};
}

#endif // ILRD_RD1645_IMINIONPROXY_HPP
