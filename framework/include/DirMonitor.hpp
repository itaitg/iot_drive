
//
// Created by bender on 3/19/25.
#ifndef  ILRD_RD1645_DIRMONITOR_HPP
#define  ILRD_RD1645_DIRMONITOR_HPP

#include <string>
#include <thread>

#include "Dispatcher.hpp"

namespace ilrd
{
///
///monitors a directory and responds according to a given @Callback
class DirMonitor 
{
public:
    ///
    /// @param path_name_ the path name of the directory
    explicit DirMonitor(const std::string& path_name_);
    ~DirMonitor();
    DirMonitor(const DirMonitor& other_) = delete;
    DirMonitor& operator=(const DirMonitor& other_) = delete;
    DirMonitor(DirMonitor&& other_) = delete;
    DirMonitor& operator=(DirMonitor&& other_) = delete;
    /// register a new callback to perform when a new file is inserted
    /// @param callback_ callback to perform when new file is inserted
    void RegisterCreate(ACallback<const std::string&>& callback_);
    /// register a new callback to perform when a new file is removed
    /// @param callback_ callback to perform when new file is removed
    void RegisterRemove(ACallback<const std::string&>& callback_);
    /// removes the callback when monitored a new file
    /// @param callback_ callback to perform when new file is inserted
    void UnregisterCreate(ACallback<const std::string&>& callback_);
    /// removes the callback when monitored a removal of a file
    /// @param callback_ callback to perform when new file is removed
    void UnregisterRemove(ACallback<const std::string&>& callback_);
    ///
    /// start monitoring (NON BLOCKING)
    void Run();

private:
    int m_notifyfd;
    int m_dirfd;
    bool m_is_running;

    void ThreadFunc();
    std::jthread m_monitor_thread;
    std::string m_pathname;
    Dispatcher<const std::string&> m_loader;
    Dispatcher<const std::string&> m_unloader;
};
}

#endif // ILRD_RD1645_DIRMONITOR_HPP
