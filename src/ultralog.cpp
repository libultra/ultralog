/*
 * Copyright (C) 2015 Ultramarin design AB <info@ultramarin.se>
 *
 * This file is part of ultralog.
 *
 * ultralog is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <ultralog.hpp>
#include <mutex>
#include <array>
#include <chrono>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <sys/syscall.h>


namespace ulog {


    static void do_log (Level log_level, const std::string& module, const std::string& format, va_list args) noexcept;
    static void stdout_callback (Level log_level,
                                 std::chrono::system_clock::time_point timestamp,
                                 const std::string& module,
                                 const std::string& message);

    static Level current_log_level {Level::info};
    static std::mutex log_mutex;
    static char* log_buf {nullptr};
    static size_t max_log_length {2048};
    static constexpr size_t min_log_length {32};
    static log_callback_t log_callback {stdout_callback};


    //----------------------------------------------------------
    //----------------------------------------------------------
    static std::string to_string (const Level& level)
    {
        switch (level) {
        case Level::silent:
            return "S";//"silent";

        case Level::fatal:
            return "F";//"fatal";

        case Level::error:
            return "E";//"error";

        case Level::warning:
            return "W";//"warning";

        case Level::info:
            return "I";//"info";

        case Level::debug:
            return "D";//"debug";

        case Level::trace:
        default:
            return "T";//"trace";
        }
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    static unsigned long get_thread_id ()
    {
        return static_cast<unsigned long> (syscall(SYS_gettid));
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void set_log_level (Level log_level) noexcept
    {
        current_log_level = log_level;
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void set_max_log_length (size_t size)
    {
        std::lock_guard<std::mutex> lock (log_mutex);
        if (size != max_log_length && size >= min_log_length) {
            if (log_buf != nullptr)
                delete[] log_buf;

            max_log_length = size;
            log_buf = new char[max_log_length];
        }
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    Level get_log_level () noexcept
    {
        return current_log_level;
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void set_callback (log_callback_t callback)
    {
        std::lock_guard<std::mutex> lock (log_mutex);
        log_callback = callback==nullptr ? stdout_callback : callback;
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void log_fatal (const std::string& module, const std::string& format, ...)
    {
        if (current_log_level < Level::fatal)
            return;
        va_list args;
        va_start (args, format);
        do_log (Level::fatal, module, format, args);
        va_end (args);
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void log_error (const std::string& module, const std::string& format, ...)
    {
        if (current_log_level < Level::error)
            return;
        va_list args;
        va_start (args, format);
        do_log (Level::error, module, format, args);
        va_end (args);
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void log_warning (const std::string& module, const std::string& format, ...)
    {
        if (current_log_level < Level::warning)
            return;
        va_list args;
        va_start (args, format);
        do_log (Level::warning, module, format, args);
        va_end (args);
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void log_info (const std::string& module, const std::string& format, ...)
    {
        if (current_log_level < Level::info)
            return;
        va_list args;
        va_start (args, format);
        do_log (Level::info, module, format, args);
        va_end (args);
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void log_debug (const std::string& module, const std::string& format, ...)
    {
        if (current_log_level < Level::debug)
            return;
        va_list args;
        va_start (args, format);
        do_log (Level::debug, module, format, args);
        va_end (args);
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void log_trace (const std::string& module, const std::string& format, ...)
    {
        if (current_log_level < Level::trace)
            return;
        va_list args;
        va_start (args, format);
        do_log (Level::trace, module, format, args);
        va_end (args);
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void log (Level log_level, const std::string& module, const std::string& format, ...)
    {
        if (current_log_level<log_level || log_level==Level::silent)
            return;
        va_list args;
        va_start (args, format);
        do_log (log_level, module, format, args);
        va_end (args);
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    void log (Level log_level, const std::string& module, const std::string& format, va_list args)
    {
        if (current_log_level<log_level || log_level==Level::silent)
            return;
        do_log (log_level, module, format, args);
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    static void do_log (Level log_level, const std::string& module, const std::string& format, va_list args) noexcept
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::lock_guard<std::mutex> lock (log_mutex);

        if (log_buf == nullptr) {
            log_buf = new char[max_log_length];
        }

        auto log_len = vsnprintf (log_buf, max_log_length, format.c_str(), args);
        if (log_len < 0)
            log_callback (log_level, now, module, "<error creating log message>");
        else if (static_cast<size_t>(log_len) >= max_log_length)
            log_callback (log_level, now, module, std::string(log_buf) + std::string("[...]"));
        else
            log_callback (log_level, now, module, std::string(log_buf));
    }


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    static void stdout_callback (Level log_level,
                                 std::chrono::system_clock::time_point ts,
                                 const std::string& module,
                                 const std::string& message)
    {
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds> (ts.time_since_epoch());
        char timestring[32];
        time_t timestamp = std::chrono::system_clock::to_time_t (ts);
        strftime (timestring, sizeof(timestring), "%F %T", localtime(&timestamp));
        std::stringstream ss;
        ss << timestring << "." << std::setfill('0') << std::setw(3)
           << (ms.count()%1000)
           << " (" << to_string(log_level) << ") "
           << "[" << get_thread_id() << "] "
           << module << ": " << message << "\n";
        std::cout << ss.str();
    }


}
