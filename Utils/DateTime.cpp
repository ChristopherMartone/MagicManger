
#include "DateTime.hpp"

DateTime& DateTime::instance() {
    static DateTime instance;
    return instance;
}

DateTime::DateTime() {}

std::string DateTime::getCurrentDateTimeString() {
    return getCurrentDateTime();
}

std::string DateTime::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

