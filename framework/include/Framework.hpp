
//
// Created by bender on 3/27/25.
#ifndef  ILRD_RD1645_FRAMEWORK_HPP
#define  ILRD_RD1645_FRAMEWORK_HPP

#include <functional>
//#include <string>

#include "DirMonitor.hpp"
#include "DLLLoader.hpp"
#include "ICommand.hpp"
#include "IInputProxy.hpp"
#include "Reactor.hpp"

namespace ilrd
{
///
///knows how to respond accordingly to inputs from given fds
class Framework 
{
public:
    /// 
    /// @param action_list_ list of: fd to listen to, what mode, @IInputProxy connected to
    /// @param plugins_dir_ name of the plugins directory
    /// @param factory_list_ list with key and command associated
    Framework(const std::vector<std::tuple<int, MODE, IInputProxy*>>& action_list_,
              const std::string& plugins_dir_,
              const std::vector<std::pair<int, std::function<std::shared_ptr<ICommand>()>>>&
                factory_list_);

    ~Framework() = default;
    Framework(const Framework& other_) = delete;
    Framework& operator=(const Framework& other_) = delete;
    Framework(Framework&& other_) = delete;
    Framework& operator=(Framework&& other_) = delete;
    ///
    ///runs the framework (BLOCKING)
    void Run();

private:
    static void InputMediator(const int& fd_, const MODE& mode_,
     IInputProxy* proxy_);

    const std::vector<std::tuple<int, MODE, IInputProxy*>>& m_action_list;

    DirMonitor m_plugin_monitor;
    Reactor m_reactor;
    DLLLoader m_plugin_loader;

    Callback<const std::string&, DLLLoader>  PluginLoad;
    Callback<const std::string&, DLLLoader>  PluginUnload;
};




}

#endif // ILRD_RD1645_FRAMEWORK_HPP
