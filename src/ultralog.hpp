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
#ifndef ULTRALOG_HPP
#define ULTRALOG_HPP

#include <string>
#include <cstdarg>
#include <functional>
#include <chrono>


/**
 * ulog is the namespace for all logging functionality in libultralog.
 */
namespace ulog {

    /**
     * A log level indicating the severity of a log message.
     */
    enum class Level {
        silent  = 0, /**< No logging will be done. */
        fatal   = 1, /**< Fatal error messages.    */
        error   = 2, /**< Error messages.          */
        warning = 3, /**< Warning messages.        */
        info    = 4, /**< Information messages.    */
        debug   = 5, /**< Debugging messages.      */
        trace   = 6  /**< Tracing messages.        */
    };


    /**
     *
     */
    using log_callback_t = std::function<void (Level log_level,
                                               std::chrono::system_clock::time_point timestamp,
                                               const std::string& module,
                                               const std::string& message)>;

    /**
     * Set the log level.
     * This will set the maximum log level that will be logged.
     * @param log_level The new log level.
     */
    void set_log_level (Level log_level) noexcept;

    /**
     * Set the maximum length of a single log message in bytes. The default is 2048.
     * If the log message should exceed the maximum length it is truncated and
     * the string "[...]" will be appended to the log message, thus making the
     * total length of the message 2053 bytes.
     * There is also a hadr coded minimum size of 32 bytes per message. Setting
     * a maximum of lower than 32 will result in a maximum of 32.
     * @param size The maximum size of a single log message.
     */
    void set_max_log_length (size_t size);

    /**
     * Return the current log level.
     */
    Level get_log_level () noexcept;

    /**
     * Set a callback that will receive log entries.
     * If no callback is set, a default callback is used that will
     * print log entries to the standard output.
     * @param callback The callback that will receive log entries.
     *                 Set this to <code>nullptr</code> to reset the callback.
     */
    void set_callback (log_callback_t callback);

    /**
     * Log a fatal error message.
     * @param module The name of the entity that is loggin the message.
     * @param format A printf-style format string followed by optional parameters.
     */
    void log_fatal (const std::string& module, const std::string& format, ...);

    /**
     * Log an error message.
     * @param module The name of the entity that is loggin the message.
     * @param format A printf-style format string followed by optional parameters.
     */
    void log_error (const std::string& module, const std::string& format, ...);

    /**
     * Log a warning message.
     * @param module The name of the entity that is loggin the message.
     * @param format A printf-style format string followed by optional parameters.
     *
     *
     */
    void log_warning (const std::string& module, const std::string& format, ...);

    /**
     * Log an information message.
     * @param module The name of the entity that is loggin the message.
     * @param format A printf-style format string followed by optional parameters.
     *
     */
    void log_info (const std::string& module, const std::string& format, ...);

    /**
     * Log a debug message.
     * @param module The name of the entity that is loggin the message.
     * @param format A printf-style format string followed by optional parameters.
     *
     */
    void log_debug (const std::string& module, const std::string& format, ...);

    /**
     * Log a trace message.
     * @param module The name of the entity that is loggin the message.
     * @param format A printf-style format string followed by optional parameters.
     *
     */
    void log_trace (const std::string& module, const std::string& format, ...);

    /**
     * Log a message.
     * @param log_level The log level of the message.
     * @param module The name of the entity that is loggin the message.
     * @param format A printf-style format string followed by optional parameters.
     */
    void log (Level log_level, const std::string& module, const std::string& format, ...);

    /**
     * Log a message.
     * @param log_level The log level of the message.
     * @param module The name of the entity that is loggin the message.
     * @param format A printf-style format string.
     * @param args Optional parameters for the format string.
     */
    void log (Level log_level, const std::string& module, const std::string& format, va_list args);
}


#endif
