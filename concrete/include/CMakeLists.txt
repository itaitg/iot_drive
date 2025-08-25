cmake_minimum_required(VERSION 3.20)




target_sources(proxys_static PRIVATE NBDProxy.hpp NBDReadArgs.hpp
        NBDWriteArgs.hpp ReadCommand.hpp WriteCommand.hpp)
target_sources(proxys_shared PRIVATE NBDProxy.hpp NBDReadArgs.hpp
        NBDWriteArgs.hpp ReadCommand.hpp WriteCommand.hpp)

target_sources(minionproxy_static PRIVATE IMinionProxy.hpp MinionProxy.hpp)
target_sources(minionproxy_shared PRIVATE IMinionProxy.hpp MinionProxy.hpp)

target_sources(responsemanager_static PRIVATE ResponseManager.hpp)
target_sources(responsemanager_shared PRIVATE ResponseManager.hpp)

target_sources(minionmanager_static PRIVATE MinionManager.hpp)
target_sources(minionmanager_shared PRIVATE MinionManager.hpp)

target_sources(uid_static PRIVATE UID.hpp)
target_sources(uid_shared PRIVATE UID.hpp)

target_sources(ataskargs_static PRIVATE ATaskArgs.hpp)
target_sources(ataskargs_shared PRIVATE ATaskArgs.hpp)


target_sources(ticket_static PRIVATE Ticket.hpp)
target_sources(ticket_shared PRIVATE Ticket.hpp)

target_sources(command_static PRIVATE ReadCommand.hpp WriteCommand.hpp)
target_sources(command_shared PRIVATE ReadCommand.hpp WriteCommand.hpp)

target_sources(response_static PRIVATE IResponse.hpp ReadResponse.hpp
        WriteResponse.hpp)
target_sources(response_shared PRIVATE IResponse.hpp ReadResponse.hpp
        WriteResponse.hpp)

target_sources(masterproxy_static PRIVATE MasterProxy.hpp)
target_sources(masterproxy_shared PRIVATE MasterProxy.hpp)

target_sources(filemanager_static PRIVATE FileManager.hpp IFileManager.hpp)
target_sources(filemanager_shared PRIVATE FileManager.hpp IFileManager.hpp)


target_sources(minion_read_command_static PRIVATE MinionReadCommand.hpp)
target_sources(minion_read_command_shared PRIVATE MinionReadCommand.hpp)

target_sources(minion_write_command_static PRIVATE MinionWriteCommand.hpp)
target_sources(minion_write_command_shared PRIVATE MinionWriteCommand.hpp)

target_sources(minion_write_args_static PRIVATE MinionWriteArgs.hpp)
target_sources(minion_write_args_shared PRIVATE MinionWriteArgs.hpp)

target_sources(minion_read_args_static PRIVATE MinionReadArgs.hpp)
target_sources(minion_read_args_shared PRIVATE MinionReadArgs.hpp)

target_sources(nbd_static PRIVATE NBD.hpp)
target_sources(nbd_shared PRIVATE NBD.hpp)