#include "fclog.h"
#include <ctime>
#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ostream;

namespace fclog
{
    static ostream cnull(0);
    static short min_log_level = static_cast<short>(Severity::INFO);
    static bool disp_time = false;

    bool doLog(Severity s)
    {
        return (static_cast<short>(s) <= min_log_level);
    }

    void Logger(Severity min_severity, bool print_timestamp)
    {
        min_log_level = static_cast<short>(min_severity);
        disp_time = print_timestamp;
    }

    fclog::Severity parseSeverity(const std::string& s)
    {
        if (s == "VERBOSE") return Severity::VERBOSE;
        if (s == "TRACE") return Severity::TRACE;
        if (s == "DEBUG") return Severity::DEBUG;
        if (s == "NOTICE") return Severity::NOTICE;
        if (s == "INFO") return Severity::INFO;
        if (s == "WARNING") return Severity::WARNING;
        if (s == "WARN") return Severity::WARN;
        if (s == "ERROR") return Severity::ERROR;
        if (s == "FATAL") return Severity::FATAL;
        if (s == "CRITICAL") return Severity::CRITICAL;
        return Severity::NONE;
    }

    inline ostream& logItem(Severity severity, const string& label, const string& color = "\033[0m" /* RESET */)
    {
        if (doLog(severity))
        {
            auto ts = [&]()
                {
                    if (disp_time)
                    {
                        std::time_t now = std::time(nullptr);
                        #if defined(_WIN32) || defined(_WIN64)
                        std::tm utm;
                        gmtime_s(&utm, &now);
                        #elif defined(__linux__)
                        std::tm utm = *std::gmtime(&now);
                        #endif
                        return std::put_time(&utm, "%F %T %Z  ");
                    }
                    else
                    {
                        return std::put_time(NULL, "  ");
                    }
                };

            return cout << color << ts() << " [" << label << "]\033[0m  ";
        }
        else
        {
            return cnull << "[" << label << "] ";
        }
    }

    ostream& FATAL()
    {
        return logItem(Severity::FATAL, "FATAL", "\033[91;1m" /*BRIGHT RED*/);
    }

    ostream& ERROR()
    {
        return logItem(Severity::ERROR, "ERROR", "\033[31;1m" /*RED*/);
    }

    ostream& WARN()
    {
        return logItem(Severity::WARNING, " WARN", "\033[33;1m" /*YELLOW*/);
    }

    ostream& INFO()
    {
        return logItem(Severity::NOTICE, " INFO", "\033[32;1m" /*GREEN*/);
    }

    ostream& DEBUG()
    {
        return logItem(Severity::DEBUG, "DEBUG", "\033[36;1m" /*CYAN*/);
    }

    ostream& TRACE()
    {
        return logItem(Severity::TRACE, "TRACE", "\033[96;1m" /*BRIGHT CYAN*/);
    }

    ostream& FATAL_IF(bool condition)
    {
        return (condition == true) ? FATAL() : cnull;
    }

    ostream& ERROR_IF(bool condition)
    {
        return (condition == true) ? ERROR() : cnull;
    }

    ostream& WARN_IF(bool condition)
    {
        return (condition == true) ? WARN() : cnull;
    }

    ostream& INFO_IF(bool condition)
    {
        return (condition == true) ? INFO() : cnull;
    }

    ostream& DEBUG_IF(bool condition)
    {
        return (condition == true) ? DEBUG() : cnull;
    }

    ostream& TRACE_IF(bool condition)
    {
        return (condition == true) ? TRACE() : cnull;
    }
}
