cmake_minimum_required(VERSION 3.20)

project(proxys)
add_library(proxys_static STATIC NBDProxy.cpp NBDReadArgs.cpp
        NBDWriteArgs.cpp ReadCommand.cpp WriteCommand.cpp)
add_library(proxys_shared SHARED NBDProxy.cpp NBDReadArgs.cpp
        NBDWriteArgs.cpp ReadCommand.cpp WriteCommand.cpp)


project(minionproxy)
add_library(minionproxy_static STATIC MinionProxy.cpp)
add_library(minionproxy_shared SHARED MinionProxy.cpp)
target_link_libraries(minionproxy_static UDP_socket TCP_Connect)

project(responsemanager)
add_library(responsemanager_static STATIC ResponseManager.cpp)
add_library(responsemanager_shared SHARED ResponseManager.cpp)

project(minionmanager)
add_library(minionmanager_static STATIC MinionManager.cpp)
add_library(minionmanager_shared SHARED MinionManager.cpp)

project(uid)
add_library(uid_static STATIC UID.cpp)
add_library(uid_shared SHARED UID.cpp)

project(ataskargs)
add_library(ataskargs_static STATIC ATaskArgs.cpp)
add_library(ataskargs_shared SHARED ATaskArgs.cpp UID.cpp)
target_link_libraries(ataskargs_static PUBLIC uid_static)




#project(messageresponse)
#add_library(messageresponse_static STATIC AMessage.cpp AMessageResponse.cpp
#        ReadMessageResponse.cpp WriteMessageResponse.cpp)
#target_link_libraries(messageresponse_static PUBLIC uid_static)

#project(amessage)
#add_library(amessage_static STATIC AMessage.cpp ReadMessageSend.cpp
#        WriteMessageSend.cpp)
#target_link_libraries(amessage_static PUBLIC uid_static)

project(amessage)
add_library(amessage_static STATIC AMessage.cpp AMessageResponse.cpp
        ReadMessageResponse.cpp
        WriteMessageResponse.cpp ReadMessageSend.cpp
        WriteMessageSend.cpp)
add_library(amessage_shared SHARED AMessage.cpp AMessageResponse.cpp
        ReadMessageResponse.cpp
        WriteMessageResponse.cpp ReadMessageSend.cpp
        WriteMessageSend.cpp)
target_link_libraries(amessage_static PUBLIC uid_static)
target_link_libraries(amessage_shared PUBLIC uid_shared)


project(ticket)
add_library(ticket_static STATIC Ticket.cpp)
add_library(ticket_shared SHARED Ticket.cpp)

project(command)
add_library(command_static STATIC ReadCommand.cpp WriteCommand.cpp)
add_library(command_shared SHARED ReadCommand.cpp WriteCommand.cpp)

project(response)
add_library(response_static STATIC ReadResponse.cpp WriteResponse.cpp)
add_library(response_shared SHARED ReadResponse.cpp WriteResponse.cpp)

project(masterproxy)
add_library(masterproxy_static STATIC MasterProxy.cpp)
add_library(masterproxy_shared SHARED MasterProxy.cpp)
target_link_libraries(masterproxy_static PUBLIC amessage_static)

project(filemanager)
add_library(filemanager_static STATIC FileManager.cpp)
add_library(filemanager_shared SHARED FileManager.cpp)

project(minionread)
add_library(minion_read_command_static STATIC MinionReadCommand.cpp MinionReadArgs.cpp
        ATaskArgs.cpp FileManager.cpp)
add_library(minion_read_command_shared SHARED MinionReadCommand.cpp MinionReadArgs.cpp
        ATaskArgs.cpp FileManager.cpp)

project(minionwrite)
add_library(minion_write_command_static STATIC MinionWriteCommand.cpp
        MinionWriteArgs.cpp ATaskArgs.cpp FileManager.cpp)
add_library(minion_write_command_shared SHARED MinionWriteCommand.cpp
        MinionWriteArgs.cpp ATaskArgs.cpp FileManager.cpp)

project(minionwriteargs)
add_library(minion_write_args_static STATIC MinionWriteArgs.cpp)
add_library(minion_write_args_shared SHARED MinionWriteArgs.cpp)

project(minionreadargs)
add_library(minion_read_args_static STATIC MinionReadArgs.cpp)
add_library(minion_read_args_shared SHARED MinionReadArgs.cpp)

project(nbd)
add_library(nbd_static STATIC NBD.cpp)
add_library(nbd_shared SHARED NBD.cpp)



