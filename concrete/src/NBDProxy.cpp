//
// Created by bender on 4/6/25.
// Approved by:


#include <cstring>
#include <Factory.hpp>
#include <linux/nbd.h>

#include "Handleton.hpp"
#include "NBDReadArgs.hpp"
#include "NBDWriteArgs.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors


ilrd::NBDProxy::NBDProxy(NBD& nbd_) : m_nbd(nbd_)
{
    Handleton::GetInstance<Factory<NBDKEY, ATaskArgs, NBDArgs>>()
        ->Register(AREAD, [](const NBDArgs& args_)
        {
            return std::make_shared<NBDReadArgs>(args_);
        });
    Handleton::GetInstance<Factory<NBDKEY, ATaskArgs, NBDArgs>>()
        ->Register(AWRITE, [](const NBDArgs& args_)
        {
            return std::make_shared<NBDWriteArgs>(args_);
        });
}

void ilrd::NBDProxy::RegisterForNewTaskArgs
        (ACallback<const std::shared_ptr<ATaskArgs>&>& callback_)
{
    m_dispatcher.Register(callback_);
}

void ilrd::NBDProxy::Reply(const UID& handle_, const bool status_, const size_t count_data_,
    const std::shared_ptr<char[]>& data_)
{
    const auto& tcp = m_nbd.GetTCP();
    std::vector<char> temp(sizeof(nbd_reply));
    auto& [magic, error, handle] = *reinterpret_cast<nbd_reply*>(temp.data());
    std::unique_lock lock(m_mutex);
    std::memcpy(handle, m_map.at(handle_).data(), sizeof(handle));
    lock.unlock();
    magic = ntohl(NBD_REPLY_MAGIC);
    error = ntohl(!status_);
    lock.lock();
    tcp.Send(temp);
    if (count_data_ > 0)
    {
        temp.resize(count_data_);
        memcpy(temp.data(), data_.get(), count_data_);
        tcp.Send(temp);
    }
}

std::shared_ptr<ilrd::ATaskArgs> ilrd::NBDProxy::GetTaskArgs(const int fd_,
                                                             const MODE mode_)
{
    (void)fd_;
    (void)mode_;

    TCP_Connect& tcp = m_nbd.GetTCP();
    std::vector<char> buffer(sizeof(nbd_request));
    std::unique_lock lock(m_mutex);
    tcp.Receive(buffer);
    lock.unlock();
    const nbd_request* request = reinterpret_cast<nbd_request*>(buffer.data());
    uint32_t len = ntohl(request->len);
    const uint32_t offset = NBD::ntohll(request->from);
    switch (ntohl(request->type))
    {
    case NBD_CMD_READ:
    {
        const NBDArgs readArgs(offset, len);
        std::shared_ptr<ATaskArgs> returnReadArgs = Handleton::GetInstance<Factory<NBDKEY,
            ATaskArgs, NBDArgs>>()->Create(AREAD, readArgs);
        lock.lock();
        std::memcpy(m_map[returnReadArgs->GetUID()].data(), request->handle, sizeof(request->handle));
        lock.unlock();
        m_dispatcher.Notify(returnReadArgs);
        return returnReadArgs;
    }
    case NBD_CMD_WRITE:
    {
        std::vector<char> temp(len);
        lock.lock();
        tcp.Receive(temp);
        lock.unlock();
        const NBDArgs writeArgs(offset, len, std::make_shared<char[]>(len));
        std::memcpy(writeArgs.m_buffer.get(), temp.data(), temp.size());
        std::shared_ptr<ATaskArgs> returnWriteArgs = Handleton::GetInstance<Factory<NBDKEY,
            ATaskArgs, NBDArgs>>()->Create(AWRITE, writeArgs);
        lock.lock();
        std::memcpy(m_map[returnWriteArgs->GetUID()].data(), request->handle, sizeof(request->handle));
        lock.unlock();
        m_dispatcher.Notify(returnWriteArgs);
        return returnWriteArgs;
    }
    default:
        throw std::runtime_error("Command not supported");
    }
}


////////////////////NBDArgs

ilrd::NBDArgs::NBDArgs(const size_t offset_, const size_t length,
    const std::shared_ptr<char[]>& buffer_): m_offset(offset_),
    m_length(length), m_buffer(buffer_){}

