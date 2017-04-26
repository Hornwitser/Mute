/// \file logging.cpp Implementation of logging streams

#include "logging.hpp"

#include <iostream>

namespace mute {


LoggingStream log;

LoggingStream& LoggingStream::source(
    std::string file,
    int line,
    std::string function
) {
    origin = {file, line, function};
    return *this;
}

std::string LoggingStream::str()
{
    std::string s = buffer.str();
    origin = {"", 0, ""};
    buffer.str(std::string{});
    return s;
}

LoggingStream& LoggingStream::operator<<(const std::string& string)
{
    buffer << string;
    return *this;
}

LoggingStream& LoggingStream::operator<<(int number)
{
    buffer << number;
    return *this;
}

LoggingStream& operator<<(
    LoggingStream& ls,
    LoggingStream& (*f)(LoggingStream&)
) {
    f(ls);
    return ls;
}

LoggingStream& endl(LoggingStream& ls)
{
    std::cout << "Log: " << ls.str() << std::endl;
    return ls;
}


} // namespace mute
