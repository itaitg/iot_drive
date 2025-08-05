//
// Created by bender on 4/20/25.
// Approved by:


#include <cstring>


#include "MasterProxy.hpp"
#include "ReadMessageResponse.hpp"
#include "WriteMessageResponse.hpp"
#include "Handleton.hpp"
#include "Factory.hpp"
#include "MinionReadArgs.hpp"
#include "MinionWriteArgs.hpp"
#include "ReadMessageSend.hpp"
#include "WriteMessageSend.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations


ilrd::MinionArgs::MinionArgs(size_t offset_, size_t length_, UID id_,
    std::shared_ptr<char[]> buffer_): m_offset(offset_),
    m_length(length_), m_id(id_), m_buffer(buffer_)
{}

ilrd::MasterProxy::MasterProxy(): m_socket("8090")
{}


std::shared_ptr<ilrd::ATaskArgs> ilrd::MasterProxy::GetTaskArgs(int fd_,
    MODE mode_)
{
    (void)fd_;
    (void)mode_;

    std::vector<char> buffer(BUFSIZ);
    std::unique_lock lock(m_mutex);
    m_socket.Receive(buffer);
    lock.unlock();


    uint32_t class_type;
    memcpy(&class_type, buffer.data() + sizeof(uint32_t), sizeof(uint32_t));

    if(class_type == READ_SEND)
    {
        ReadMessageSend message;
        message.FromBuffer(buffer.data() + 2*sizeof(uint32_t));
        MinionArgs args(message.GetOffset(), message.GetLength(), message.GetUID());
        return std::make_shared<MinionReadArgs>(args);
    }

    WriteMessageSend message;
    message.FromBuffer(buffer.data() + 2*sizeof(uint32_t));

    auto buff = std::shared_ptr<char[]>(new char[message.GetLength()]);
    memcpy(buff.get(), message.GetStr(), message.GetLength());

    MinionArgs args(message.GetOffset(), message.GetLength(), message.GetUID
            (), buff);
    return std::make_shared<MinionWriteArgs>(args);
}

void ilrd::MasterProxy::SendReadResponse(const bool status_, const UID id_, const size_t length_,
    char* buffer_)
{
    ReadMessageResponse message(status_, id_, buffer_, length_);
    std::vector<char> buffer(message.GetSize());
    message.ToBuffer(buffer.data());
    std::unique_lock lock(m_mutex);
    m_socket.Send(buffer);
}

void ilrd::MasterProxy::SendWriteResponse(bool status_, UID id_)
{
    WriteMessageResponse message(status_, id_);
    std::vector<char> buffer(message.GetSize());
    message.ToBuffer(buffer.data());
    std::unique_lock lock(m_mutex);
    m_socket.Send(buffer);
}

int ilrd::MasterProxy::GetSocketFD() const
{
    return m_socket.Getfd();
}

