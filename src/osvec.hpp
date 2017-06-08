// \brief Various utilities
#ifndef MUTE_UTILS_HPP
#define MUTE_UTILS_HPP

#include "logging.hpp"

#include <map>
#include <utility>
#include <vector>

namespace mute {


/**
 * \brief Insert std::vector into logging stream
 *
 * Places the provided std::vector into the logging stream by outputting
 * each element as a comma separated list inside [] brackets.
 *
 * \return The \c LoggingStream opererated on, allowing multiple stream
 *         operations to be chained.
 *
 * \ingroup logging
 */
template <typename T>
inline LoggingStream& operator << (LoggingStream& ls, std::vector<T> v)
{
    ls << "[";

    if (!v.empty())
    for (auto i=v.begin(), end=v.end();;) {
        ls << *i;
        if (++i == end) break;
        ls << ", ";
    }

    ls << "]";

    return ls;
}

template <typename Key, typename Value>
inline LoggingStream& operator << (LoggingStream& ls, std::map<Key, Value> m)
{
    ls << "{";

    if (!m.empty())
    for (auto i=m.begin(), end=m.end();;) {
        ls << i->first << ": " << i->second;
        if (++i == end) break;
        ls << ", ";
    }

    ls << "}";

    return ls;
}


} // namespace mute

#endif // MUTE_UTILS_HPP
