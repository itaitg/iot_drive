cmake_minimum_required(VERSION 3.20)


project(thread_safe_queue)
add_executable(thread_safe_queue WaitableQueueTest.cpp)


project(thread_pool)
add_executable(thread_pool TP_Test.cpp)
target_link_libraries(thread_pool thread_pool_static)

project(factory)
add_executable(factory FactoryTest.cpp)
target_link_libraries(factory handleton_shared)

project(singleton)
add_executable(singleton SingletonTest.cpp)

project(handleton)
add_executable(handleton handleton_test.cpp)
target_link_libraries(handleton handleton_shared)

add_library(Handletondll1 SHARED Handletondll1.cpp)
link_libraries(Handletondll1 handleton_shared)
add_library(Handletondll2 SHARED Handletondll2.cpp)
link_libraries(Handletondll2 handleton_shared)

project(logger)
add_executable(logger LoggerTest.cpp)
target_link_libraries(logger logger_static)

project(dispatcher)
add_executable(dispatcher DispatcherTest.cpp)

project(dirmonitor)
add_executable(dirmonitor DirMonitorTest.cpp)
target_link_libraries(dirmonitor dirmonitor_static)

add_library(dlltest SHARED DLLLoaderTest.cpp)

project(reactor)
add_executable(reactor ReactorTest.cpp)
target_link_libraries(reactor reactor_static)

project(schedulercpp)
add_executable(schedulercpp SchedulerTest.cpp)
target_link_libraries(schedulercpp schedulercpp_static)

project(synctask)
add_executable(synctask ASyncInjectionTest.cpp)
target_link_libraries(synctask asyncinjection_static)

project(framework)
add_executable(framework Master.cpp)
target_link_libraries(framework framework_static proxys_static uid_static
        minionproxy_static responsemanager_static minionmanager_static
        ataskargs_static amessage_static ticket_static command_static
        response_static logger_static nbd_static)

add_library(plugintest SHARED FWPluginTest.cpp)



