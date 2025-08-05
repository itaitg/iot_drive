//
// Created by bender on 3/19/25.
// Approved by:

#include <cerrno>
#include <cstring>
#include <sys/inotify.h>

#include "DirMonitor.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations

ilrd::DirMonitor::DirMonitor(const std::string& path_name_): m_notifyfd(),
m_dirfd(), m_is_running(false), m_pathname(path_name_)
{
    m_notifyfd = inotify_init();
    if(m_notifyfd == -1)
    {
        throw std::runtime_error("inotify_init");
    }
    m_dirfd = inotify_add_watch(m_notifyfd, path_name_.c_str(),
    IN_DELETE | IN_CLOSE_WRITE);
    if(m_dirfd == -1)
    {
        throw std::runtime_error("inotify_add_watch");
    }
}

ilrd::DirMonitor::~DirMonitor()
{
    m_is_running = false;

    inotify_rm_watch(m_notifyfd, m_dirfd);
    try
    {
        m_monitor_thread.join();
    }
    catch (...) {}


    close(m_notifyfd);
    close(m_dirfd);
}

void ilrd::DirMonitor::RegisterCreate(ACallback<const std::string&>& callback_)
{
    m_loader.Register(callback_);
}

void ilrd::DirMonitor::RegisterRemove(ACallback<const std::string&>& callback_)
{
    m_unloader.Register(callback_);
}

void ilrd::DirMonitor::UnregisterCreate(ACallback<const std::string&>& callback_)
{
    m_loader.Unregister(callback_);
}

void ilrd::DirMonitor::UnregisterRemove(ACallback<const std::string&>& callback_)
{
    m_unloader.Unregister(callback_);
}

void ilrd::DirMonitor::Run()
{
    m_monitor_thread = std::jthread([this] {ThreadFunc();});
}

void ilrd::DirMonitor::ThreadFunc()
{
    m_is_running = true;

    while(m_is_running)
    {
            char buffer[999999];

            ssize_t size = read(m_notifyfd, &buffer, 999999);
            if(size == -1 && errno != EAGAIN)
            {
                throw std::runtime_error("read ");
            }

            int i = 0;
            while(i < size)
            {
                const auto ie = reinterpret_cast<inotify_event*>(&buffer[i]);
                if (ie->mask & IN_CLOSE_WRITE)
                {
                    m_loader.Notify( m_pathname + "/" + std::string(ie->name));
                }
                else if (ie->mask & IN_DELETE)
                {
                    m_unloader.Notify(m_pathname + "/" + std::string(ie->name));
                }
                i += sizeof(inotify_event) + ie->len;
            }
        }
    }

