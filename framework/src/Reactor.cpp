//
// Created by bender on 3/23/25.
// Approved by:liad


//////////////////include


#include "Reactor.hpp"



//////////////////static declarations

//////////////////constructors

//////////////////static implementations


ilrd::Reactor::Reactor(IListener* listener_): m_listen(listener_), m_is_running(false)
{}

ilrd::Reactor::~Reactor()
{
    delete m_listen;
}

void ilrd::Reactor::Register(int fd_, MODE mode_,const
                             std::function<void(int, MODE)>& func_)
{
    m_map[{fd_, mode_}] = func_;
    m_listen_list.emplace_back(fd_, mode_);
}

void ilrd::Reactor::Unregister(int fd_, MODE mode_)
{
    m_map.erase({fd_, mode_});
    std::erase(m_listen_list, std::make_pair(fd_, mode_));
}


void ilrd::Reactor::Run()
{
    m_is_running = true;

    while(m_is_running)
    {
        std::vector<std::pair<int, MODE>> react_to = m_listen->Listen(m_listen_list);
        for(const auto& pair : react_to)
        {
            std::apply(m_map[pair], pair);
        }
    }
}

void ilrd::Reactor::Stop()
{
    m_is_running = false;
}
