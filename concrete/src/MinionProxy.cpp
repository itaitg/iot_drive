//
// Created by bender on 4/6/25.
// Approved by:

#include <iostream>

#include "MinionProxy.hpp"

#include <cstring>

#include "Handleton.hpp"
#include "Logger.hpp"
#include "ReadMessageResponse.hpp"
#include "ReadMessageSend.hpp"
#include "WriteMessageSend.hpp"
#include "Factory.hpp"


//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::MinionProxy::MinionProxy(const char* port_, const char* ip_): m_socket(port_, ip_), m_map()
{}

void ilrd::MinionProxy::SendWriteTask(const size_t offset_, const size_t length_, UID& id_,
    const std::shared_ptr<const char[]>& data_,
    const std::function<void(const std::shared_ptr<TaskResult>&)>& OnDone)
{
    Handleton::GetInstance<Logger>()->Log("Sent Write to minion",
        Logger::DEBUG);
    {
        std::unique_lock lock(m_mutex);
        m_map.emplace(id_, OnDone);
    }

    const auto message = std::make_shared<WriteMessageSend>(offset_, length_, data_.get(), id_);
    std::vector<char> buffer;
    buffer.resize(message->GetSize());

    message->ToBuffer(buffer.data());
    std::unique_lock lock(m_mutex);
    m_socket.Send(buffer);
}

void ilrd::MinionProxy::SendReadTask(size_t offset_, size_t length_, UID& id_,
    const std::function<void(const std::shared_ptr<TaskResult>&)>& OnDone)
{
    Handleton::GetInstance<Logger>()->Log("Sent Read to Minion",
        Logger::DEBUG);
    {
        std::unique_lock lock(m_mutex);
        m_map.emplace(id_, OnDone);
    }

    const std::shared_ptr<AMessage> message = std::make_shared<ReadMessageSend>(offset_,
        length_, id_);
    std::vector<char> buffer;
    buffer.resize(message->GetSize());
    message->ToBuffer(buffer.data());
    std::unique_lock lock(m_mutex);
    m_socket.Send(buffer);
}

int ilrd::MinionProxy::GetMinionFD()
{
    return m_socket.Getfd();
}

void ilrd::MinionProxy::OnMinionFDWakeUp()/// waiting for ticket
{
    std::vector<char> buffer(BUFSIZ);

    std::unique_lock lock(m_mutex);
    m_socket.Receive(buffer);
    lock.unlock();

    uint32_t class_type;
    memcpy(&class_type, buffer.data() + sizeof(uint32_t), sizeof(uint32_t));

    const auto message = Handleton::GetInstance<Factory<CLASS_TYPE,
        AMessageResponse>>()->Create(static_cast<CLASS_TYPE>(class_type));

    message->FromBuffer(buffer.data() + 2*sizeof(uint32_t));

    Handleton::GetInstance<Logger>()->Log("Received Response From Minion",
        Logger::DEBUG);
    lock.lock();
    if(class_type == READ_RESPONSE)
    {
        m_map[message->GetUID()](std::make_shared<TaskResult> (message->GetStatus(),
            message->GetUID(), static_cast<ReadMessageResponse*>(message.get())->GetLengthMessage(),
            static_cast<ReadMessageResponse*>(message.get())->GetStr()));
    }
    else
    {
        m_map[message->GetUID()](std::make_shared<TaskResult> (message->GetStatus(),
                message->GetUID(), 0,nullptr));
    }
    m_map.erase(message->GetUID());
}
