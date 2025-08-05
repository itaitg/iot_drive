//
// Created by bender on 3/29/25.
//


#include <iostream>
#include <optional>

#include "ReadCommand.hpp"
#include "WriteCommand.hpp"
#include "Framework.hpp"
#include "MinionManager.hpp"
#include "NBDProxy.hpp"
#include "Handleton.hpp"
#include "MinionProxy.hpp"
#include "ResponseManager.hpp"
#include "ThreadPool.hpp"


std::shared_ptr<ilrd::ICommand> CreateReadCommand(){return
    std::make_shared<ilrd::ReadCommand>();}
std::shared_ptr<ilrd::ICommand> CreateWriteCommand(){return
    std::make_shared<ilrd::WriteCommand>();}





void FrameworkTest()
{
    ilrd::NBD nbd;
    nbd.Init("/dev/nbd2");
    ilrd::NBDProxy nbd_proxy(nbd);

    std::vector<std::tuple<int, ilrd::MODE, ilrd::IInputProxy*>> input_proxies = { std::make_tuple(nbd.GetTCP().Getfd(), ilrd::READ, &nbd_proxy)};
    std::vector<std::pair<int, std::function<std::shared_ptr<ilrd::ICommand>()>>> factory_list =
        {std::make_pair(0, CreateReadCommand), std::make_pair(1, CreateWriteCommand)};


    ilrd::Framework framework(input_proxies,"./plugins", factory_list);
    ilrd::Handleton::GetInstance<ilrd::ResponseManager>()->Init(nbd_proxy);

    std::vector<std::shared_ptr<ilrd::IMinionProxy>> minions;

    minions.emplace_back(std::make_shared<ilrd::MinionProxy>("8092", "10.1.0.49"));
    minions.emplace_back(std::make_shared<ilrd::MinionProxy>("8091", "10.1.0.130"));
    minions.emplace_back(std::make_shared<ilrd::MinionProxy>("8090", "127.0.0.1"));

    ilrd::Handleton::GetInstance<ilrd::MinionManager>()->Init(4*1024*1024, minions);
    framework.Run();
}



int main()
{
    FrameworkTest();

    return 0;
}
