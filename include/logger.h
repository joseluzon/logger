// code-licenser auto-generated license header

// Copyright (C) 2019 Jose Luzón Martín
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <mutex>
#include <map>
#include <chrono>
#include <iomanip>

#define LOG_FATAL(log, ...) log.print< jluzoncpp::logger::LoggerLevel::Fatal >(__VA_ARGS__)
#define LOG_ERROR(log, ...) log.print< jluzoncpp::logger::LoggerLevel::Error >(__VA_ARGS__)
#define LOG_WARNING(log, ...) log.print< jluzoncpp::logger::LoggerLevel::Warning >(__VA_ARGS__)
#define LOG_INFO(log, ...) log.print< jluzoncpp::logger::LoggerLevel::Info >(__VA_ARGS__)
#define LOG_TRACE(log, ...) log.print< jluzoncpp::logger::LoggerLevel::Trace >(__VA_ARGS__)
#define LOG_DEBUG(log, ...) log.print< jluzoncpp::logger::LoggerLevel::Debug >(__VA_ARGS__)

namespace jluzoncpp {
namespace  logger {

enum class LoggerLevel
{
    None        = 0,
    Fatal       = 1,
    Error       = 2,
    Warning     = 3,
    Info        = 4,
    Trace       = 5,
    Debug       = 6,

    // always last!
    MaxLevels
};

template<typename LogPolicy> class Logger
{
public:
    Logger(const std::string& name, LoggerLevel minLevel = LoggerLevel::None) noexcept(false) :
        m_name(name),
        m_policy(nullptr),
        m_minLevel(minLevel),
        m_currentLevel(LoggerLevel::None)
    {
        m_policy = new LogPolicy;
        if (m_policy == nullptr)
            throw std::runtime_error("LOGGER: Unable to create the logger instance");

        m_policy->open(m_name);
    }

    ~Logger() {}

    template<LoggerLevel level, class...Args> void print(Args...args)
    {
        m_writeMutex.lock();

        if (m_minLevel > LoggerLevel::None && level > LoggerLevel::None && level <= m_minLevel)
        {
            m_currentLevel = level;
            print_impl(args...);
        }

        m_writeMutex.unlock();
    }

private:
    // Hidden:
    Logger(const Logger& other);
    Logger& operator = (const Logger& other);
    //

    std::string m_name = "";
    LogPolicy* m_policy = nullptr;
    LoggerLevel m_minLevel;
    LoggerLevel m_currentLevel;
    std::stringstream m_logStream;
    std::mutex m_writeMutex;

    typedef std::map<LoggerLevel, std::string> LoggerLevel2Str;
    LoggerLevel2Str m_level2str =
    {
        { LoggerLevel::None,    "NONE"},
        { LoggerLevel::Fatal,   "FATAL"},
        { LoggerLevel::Error,   "ERROR"},
        { LoggerLevel::Warning, "WARNING"},
        { LoggerLevel::Info,    "INFO"},
        { LoggerLevel::Trace,   "TRACE"},
        { LoggerLevel::Debug,   "DEBUG"}
    };

    std::string getTime()
    {
        auto time_now       = std::chrono::system_clock::now();
        auto fraction       = time_now - std::chrono::time_point_cast<std::chrono::seconds>(time_now);
        auto milliseconds   = std::chrono::duration_cast<std::chrono::milliseconds>(fraction);

        time_t raw_time = std::chrono::system_clock::to_time_t(time_now);

        char time_str [ 25 ] = { '\0' };
        std::strftime(time_str, 25, "%F %T", std::localtime(&raw_time));

        std::stringstream timestr;
        timestr.str("");

        timestr << time_str << "." << std::right << std::setfill('0') << std::setw(4) << milliseconds.count(); // ms

        return timestr.str();
    }

    std::string getLogLineHeader()
    {
        std::stringstream header;
        header << getTime() << " "
               << std::left << std::setfill(' ') << std::setw(8) << m_level2str[m_currentLevel] << " "
               << std::left << std::setfill(' ') << std::setw(10) << m_name;

        return header.str();
    }

    //Core printing functionality
    void print_impl()
    {
        m_policy->write( getLogLineHeader() + m_logStream.str() );
        m_logStream.str("");
    }

    template<class First, class...Rest> void print_impl(First parm1, Rest...parm)
    {
        m_logStream << parm1 << " ";
        print_impl(parm...);
    }
};

} // logger
} // jluzoncpp

#endif // LOGGER_H
