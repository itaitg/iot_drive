//
// Created by bender on 3/27/25.
// Approved by:


//////////////////include

#include "Framework.hpp"
#include "Factory.hpp"
#include "FW_TPTask.hpp"
#include "Handleton.hpp"
#include "ThreadPool.hpp"

ilrd::Framework::Framework(const std::vector<std::tuple<int, MODE, IInputProxy*>>& action_list_,
    const std::string& plugins_dir_, const std::vector<std::pair<int,
    std::function<std::shared_ptr<ICommand>()>>>& factory_list_):
    m_action_list(action_list_), m_plugin_monitor(plugins_dir_), PluginLoad(m_plugin_loader,
    &DLLLoader::Reload), PluginUnload(m_plugin_loader,&DLLLoader::Unload)
{
    for(auto [fd, mode, proxy] : action_list_)
    {
        m_reactor.Register(fd, mode, [proxy](const int& fd_, const MODE& mode_)
            {return InputMediator(fd_, mode_, proxy);});
    }

    for(auto [key, command] : factory_list_)
    {
        Handleton::GetInstance<Factory<int, ICommand>>()->Register(key, command);
    }

    m_plugin_monitor.RegisterCreate(PluginLoad);
    m_plugin_monitor.RegisterRemove(PluginUnload);
}

void ilrd::Framework::Run()
{
    m_plugin_monitor.Run();
    m_reactor.Run();
}

void ilrd::Framework::InputMediator(const int& fd_, const MODE& mode_,
IInputProxy* proxy_)
{
    std::shared_ptr<ITaskArgs> pTaskArgs = proxy_->GetTaskArgs(fd_, mode_);
    if(pTaskArgs == nullptr)
    {
        return;
    }

    const auto new_task = std::make_shared<FW_TPTask>(pTaskArgs);

    Handleton::GetInstance<ThreadPool>()->AddTask(new_task);
}
