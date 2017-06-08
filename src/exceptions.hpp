// \file exceptions.hpp

#ifndef MUTE_EXCEPTIONS_HPP
#define MUTE_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace mute {


/**
 * \brief Thrown when inserting a conflicting item
 *
 * Mute specific error class for reporting insertion errors in mappings
 * due to an item with that specific key already existing.
 */
class KeyExistsError: public std::logic_error {
public:
    using logic_error::logic_error;
};

/**
 * \brief Thrown when looking up a non-existing item
 *
 * Mute specific error class for reporting lookup errors in mappings due
 * to there being no item associated with the key in question.
 */
class KeyError: public std::logic_error {
public:
    using logic_error::logic_error;
};

/**
 * \brief Thrown when accessing a proxy object to a deleted node
 *
 * Mute specific error class for reporting access through a proxy object
 * pointing to a node that has been deleted from the graph.
 */
class ProxyExpired: public std::logic_error {
public:
    using logic_error::logic_error;
};


} // namespace mute

#endif // MUTE_EXCEPTIONS_HPP
