#include <ultralog.hpp>
#include <iostream>

using namespace std;

static void log_all (int param)
{
    ulog::log_fatal   ("test_log", "Try to lo a fatal message, param %d", param);
    ulog::log_error   ("test_log", "Try to lo an error message, param %d", param);
    ulog::log_warning ("test_log", "Try to lo a warning message, param %d", param);
    ulog::log_info    ("test_log", "Try to lo an info message, param %d", param);
    ulog::log_debug   ("test_log", "Try to lo a debug message, param %d", param);
    ulog::log_trace   ("test_log", "Try to lo a trace message, param %d", param);
}



int main (int args, char* argv[])
{
    cout << "Use default log level:" << endl;
    log_all (1);
    cout << endl;

    cout << "Set log level: ulog::Level::trace" << endl;
    ulog::set_log_level (ulog::Level::trace);
    log_all (2);
    cout << endl;

    cout << "Set log level: ulog::Level::debug" << endl;
    ulog::set_log_level (ulog::Level::debug);
    log_all (3);
    cout << endl;

    cout << "Set log level: ulog::Level::info" << endl;
    ulog::set_log_level (ulog::Level::info);
    log_all (4);
    cout << endl;

    cout << "Set log level: ulog::Level::warning" << endl;
    ulog::set_log_level (ulog::Level::warning);
    log_all (5);
    cout << endl;

    cout << "Set log level: ulog::Level::error" << endl;
    ulog::set_log_level (ulog::Level::error);
    log_all (6);
    cout << endl;

    cout << "Set log level: ulog::Level::fatal" << endl;
    ulog::set_log_level (ulog::Level::fatal);
    log_all (7);
    cout << endl;

    cout << "Set log level: ulog::Level::silent" << endl;
    ulog::set_log_level (ulog::Level::silent);
    log_all (8);
    cout << endl;
}
