//
// Created by bender on 3/19/25.


#include <iostream>

#include "DirMonitor.hpp"
#include "DLLLoader.hpp"


void DirMonitorTest()
{
    ilrd::DirMonitor monitor("./plugins");
    ilrd::DLLLoader obj;
    ilrd::Callback<const std::string&, ilrd::DLLLoader> FuncLoad(obj,
    &ilrd::DLLLoader::Load);
    ilrd::Callback<const std::string&, ilrd::DLLLoader> FuncUnload(obj,
&ilrd::DLLLoader::Unload);

    monitor.RegisterCreate(FuncLoad);
    monitor.RegisterRemove(FuncUnload);

    monitor.Run();
    while(true);
}

int main()
{

    DirMonitorTest();

    return 0;
}
