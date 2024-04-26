#pragma once

#include <iostream>

namespace fclog
{
    /// <summary>
    /// NOTE: These severity levels do *NOT* match the `syslog` standard
    ///   1. https://datatracker.ietf.org/doc/html/rfc5424
    ///   2. https://en.wikipedia.org/wiki/Syslog#Severity_level
    /// </summary>
    enum class Severity : short
    {
        NONE = 0,
        FATAL = 1,
        CRITICAL = 1,
        ERROR = 2,
        WARN = 3,
        WARNING = 3,
        INFO = 4,
        NOTICE = 4,
        DEBUG = 5,
        TRACE = 6,
        VERBOSE = 6,

        COUNT = 7
    };

    void Logger(fclog::Severity min_severity = fclog::Severity::INFO, bool print_timestamp = false);

    fclog::Severity parseSeverity(const std::string& s);

    bool doLog(fclog::Severity s);

    std::ostream& FATAL();
    std::ostream& ERROR();
    std::ostream& WARN();
    std::ostream& INFO();
    std::ostream& DEBUG();
    std::ostream& TRACE();

    std::ostream& FATAL_IF(bool condition);
    std::ostream& ERROR_IF(bool condition);
    std::ostream& WARN_IF(bool condition);
    std::ostream& INFO_IF(bool condition);
    std::ostream& DEBUG_IF(bool condition);
    std::ostream& TRACE_IF(bool condition);

} //! namespace fclog
