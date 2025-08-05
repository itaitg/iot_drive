//
// Created by bender on 3/17/25.
// Approved by:


//////////////////include

#include <chrono>
#include <iostream>
#include <iomanip>

#include "Logger.hpp"

//////////////////static implementations
ilrd::Logger::Logger(): m_log("log.txt"), m_is_running(true)
{
    m_LUT[DEBUG] = "DEBUG";
    m_LUT[WARNING] = "WARNING";
    m_LUT[ERROR] = "ERROR";
    m_LUT[INFO] = "INFO";
    m_log_thread = std::jthread([this] {LogFunc();});
}

ilrd::Logger::~Logger()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    m_is_running = false;
    m_queue.Push({now_c, INFO,"Exit successful"});
}

void ilrd::Logger::Log(const std::string& str_, const SEVERITY type_)
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    m_queue.Push(std::make_tuple(now_c, type_, str_));
}

void ilrd::Logger::LogFunc()
{
    std::tuple< std::time_t, SEVERITY, std::string> data;

    while(m_is_running)
    {
        m_queue.Pop({data});
        m_log << std::put_time(std::localtime(&std::get<std::time_t>(data)),
            "%d-%m-%Y %H:%M ") << m_LUT[std::get<SEVERITY>(data)] << " " <<
            std::get<std::string>(data) << std::endl;
    }
    while(!m_queue.IsEmpty())
    {
        m_queue.Pop({data});
        m_log << std::put_time(std::localtime(&std::get<std::time_t>(data)),
            "%d-%m-%Y %H:%M ") << m_LUT[std::get<SEVERITY>(data)] << " " <<
            std::get<std::string>(data) << std::endl;
    }

}
