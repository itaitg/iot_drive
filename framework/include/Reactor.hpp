
//
// Created by bender on 3/23/25.
#ifndef  ILRD_RD1645_REACTOR_HPP
#define  ILRD_RD1645_REACTOR_HPP


#include <functional>
#include <map>

#include "LinuxListener.hpp"

namespace ilrd
{

class Reactor 
{
public:
    ///
    /// @param listener_ must be provided new
    explicit Reactor(IListener* listener_ = new LinuxListener());
    ~Reactor();

    Reactor(const Reactor& other_) = delete;
    Reactor& operator=(const Reactor& other_) = delete;
    Reactor(Reactor&& other_) = delete;
    Reactor& operator=(Reactor&& other_) = delete;
    /// register's a new @Callback to Run when the @FD  iw awoken
    /// @param fd_ the file descriptor to @listen to
    /// @param mode_ the @MODE to expect
    /// @param func_ the function to run
    void Register(int fd_, MODE mode_,const std::function<void(int, MODE)>&
                  func_);
    void Unregister(int fd_, MODE mode_);
    /// Runs the reactor (BLOCKING)
    void Run();
    /// stops the @Reactor (must be inserted as a func)
    void Stop();

private:
    std::map<std::pair<int, MODE>, std::function<void(int,MODE)>> m_map;
    IListener* m_listen;
    std::vector<std::pair<int, MODE>> m_listen_list;
    bool m_is_running;
};
}

#endif // ILRD_RD1645_REACTOR_HPP
