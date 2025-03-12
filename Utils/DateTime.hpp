#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class DateTime {
    public:
        static DateTime& instance();
        std::string getCurrentDateTimeString();
    private:
        DateTime();
        std::string getCurrentDateTime();
};

#endif