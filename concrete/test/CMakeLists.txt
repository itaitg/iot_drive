cmake_minimum_required(VERSION 3.20)

project(amessage)
add_executable(amessage AMessageTest.cpp)
target_link_libraries(amessage amessage_static)

project(minion)
add_executable(minion Minion.cpp)
target_link_libraries(minion framework_static minion_read_args_static minion_write_args_static
 minion_write_command_static minion_read_command_static filemanager_static
        masterproxy_static response_static uid_static UDP_socket)

add_executable(create_file FileCreator.cpp)
