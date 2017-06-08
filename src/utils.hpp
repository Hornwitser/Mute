/// \file utils.hpp Various utilities

#ifndef MUTE_UTILS_HPP
#define MUTE_UTILS_HPP

#include <string>
#include <sstream>

namespace mute {

/**
 * \brief Variadict fold expression helper
 *
 * This \p struct is a workaround for the lack of folding operators for
 * variadict arguments.  It avoids the need to create recursive
 * functions for simple expressions.
 *
 * Normally, all you can do with parameter packs is unpack them to a
 * function call.  Due to the undefined order of evaluation for the
 * parameters to a functions it's not possible to create a function that
 * does nothing with an arbitrary number of arguments to simulate
 * folding.  But the brace-initializer syntax for constructing objects
 * has the special property that arguments passed in it is evaluated
 * strictly in order, even when this brace initalizer list ends up
 * calling a constructor.
 *
 * \warning It's inmportant to use the brace syntax when using this,
 *          otherwise the order of evaluation of the fold expression
 *          will be undefined.
 *
 * \par Example
 * \code
 * template <typename... Ts>
 * void print(Ts... parts) {
 *     fold{std::cout << parts...};
 *     // Note the usage of braces and not parenthesis.
 * }
 * \endcode
 */
struct fold {
    template <typename... Ts> fold(Ts&...) {}
};

/**
 * \brief String constructor helper
 *
 * Creates a std::string by passing each argument to a string stream as
 * a << output operation and then returning the resulting string.
 */
template <typename... Ts>
std::string compose(Ts... parts) {
    std::ostringstream result;
    fold{result << parts...};
    return result.str();
}


} // namespace mute

#endif // MUTE_UTILS_HPP
