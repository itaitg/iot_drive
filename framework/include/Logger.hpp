
//
// Created by bender on 3/17/25.
#ifndef  ILRD_RD1645_LOGGER_HPP
#define  ILRD_RD1645_LOGGER_HPP

#include <string>
#include <fstream>
#include <thread>

#include "WaitableQueue.hpp"


namespace ilrd
{
///
///Log to a file events
///must use @Handleton
///the Logger path: .log.txt
class Logger
{
public:
    friend class Handleton;
    Logger(const Logger& other_) = delete;
    Logger& operator=(const Logger& other_) = delete;

    enum SEVERITY
    {
        DEBUG,
        WARNING,
        ERROR,
        INFO,
        NUM_OF_SEVERITY
    };

    ///
    /// @param str_ string for documentation
    /// @param type_ type of comment to log
    /// must be called using @Handleton
    void Log(const std::string& str_, SEVERITY type_);
    ~Logger();

private:
    Logger();
    std::ofstream m_log;
    WaitableQueue<std::tuple< std::time_t, SEVERITY, std::string>> m_queue;
    std::jthread m_log_thread;
    std::string m_LUT[NUM_OF_SEVERITY];
    bool m_is_running;
    void LogFunc();
};
}


#endif // ILRD_RD1645_LOGGER_HPP
