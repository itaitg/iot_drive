cmake_minimum_required(VERSION 3.20)


project(thread_pool)
add_library(thread_pool_static STATIC ThreadPool.cpp)
add_library(thread_pool_shared SHARED ThreadPool.cpp)

project(handleton)
add_library(handleton_shared SHARED Handleton.cpp)


project(logger)
add_library(logger_static STATIC Logger.cpp)
add_library(logger_shared SHARED Logger.cpp)
target_link_libraries(logger_shared PRIVATE handleton_shared)
target_link_libraries(logger_static PRIVATE handleton_shared)

project(dirmonitor)
add_library(dirmonitor_static STATIC DirMonitor.cpp DLLLoader.cpp)
add_library(dirmonitor_shared SHARED DirMonitor.cpp DLLLoader.cpp)

project(reactor)
add_library(reactor_static STATIC Reactor.cpp LinuxListener.cpp)
add_library(reactor_shared SHARED Reactor.cpp LinuxListener.cpp)

project(schedulercpp)
add_library(schedulercpp_static STATIC Scheduler.cpp)
add_library(schedulercpp_shared SHARED Scheduler.cpp)
target_link_libraries(schedulercpp_shared PRIVATE handleton_shared)
target_link_libraries(schedulercpp_static PRIVATE handleton_shared)

project(synctask)
add_library(asyncinjection_static STATIC ASyncInjection.cpp Scheduler.cpp)
add_library(asyncinjection_shared SHARED ASyncInjection.cpp Scheduler.cpp)
target_link_libraries(asyncinjection_static PRIVATE handleton_shared)
target_link_libraries(asyncinjection_shared PRIVATE handleton_shared)

project(master)
add_library(framework_static STATIC FW_TPTask.cpp Framework.cpp)
add_library(framework_shared SHARED FW_TPTask.cpp Framework.cpp)
target_link_libraries(framework_static PRIVATE handleton_shared
        thread_pool_static reactor_static dirmonitor_static
        asyncinjection_static logger_static amessage_static)



add_library(UDP_socket STATIC UDP_socket.cpp Socket.cpp)
add_library(TCP_Server STATIC TCP_Listener.cpp TCP_Connect.cpp Socket.cpp)
add_library(TCP_Connect STATIC TCP_Connect.cpp Socket.cpp)





