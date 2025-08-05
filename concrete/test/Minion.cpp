//
// Created by bender on 4/20/25.


#include "Framework.hpp"
#include "Handleton.hpp"
#include "MasterProxy.hpp"
#include "MinionReadCommand.hpp"
#include "MinionWriteCommand.hpp"



int main()
{

    int fd = ilrd::Handleton::GetInstance<ilrd::MasterProxy>()->GetSocketFD();

    std::vector<std::tuple<int, ilrd::MODE, ilrd::IInputProxy*>>
            input_proxies = { std::make_tuple(fd, ilrd::READ, ilrd::Handleton::GetInstance<ilrd::MasterProxy>())};
    std::vector<std::pair<int, std::function<std::shared_ptr<ilrd::ICommand>()>>> factory_list =
        {
                std::make_pair(0, []
            {return std::make_shared<ilrd::MinionReadCommand>();}),
                std::make_pair(1, []
            {return std::make_shared<ilrd::MinionWriteCommand>();})
        };


    ilrd::Framework framework(input_proxies,"./plugins", factory_list);

    framework.Run();

    return 0;
}
