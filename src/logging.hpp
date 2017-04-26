/// \file logging.hpp Logging streams

#ifndef MUTE_LOGGING_HPP
#define MUTE_LOGGING_HPP

#include <sstream>
#include <string>

namespace mute {


/**
 * \defgroup logging Logging
 * @{
 *
 * Application logging in Mute is primarily done with the \ref MUTE_LOG
 * macro defined in logging.hpp.  Items to be logged are passed to this
 * macro as if it was an ostream from the standard library, the
 * difference being that the logging system treats most objects defined
 * in this project as native objects instead of trying to convert them
 * to a stream of characters.  Metadata belonging to items passed is
 * also stored.
 */

/**
 * \brief High level logging stream
 *
 * Object based logging facility providing capabilites for outputting
 * objects related to information and debugging in a way that lets extra
 * metadata be provided with these objects.
 *
 * \sa MUTE_LOG mute::log
 */
class LoggingStream {
    struct Source {
        std::string file;
        int line = 0;
        std::string function;
    } origin;

    std::stringstream buffer;

public:
    LoggingStream() = default;
    LoggingStream(const LoggingStream&) = delete;
    LoggingStream& operator=(const LoggingStream&) = delete;

    /**
     * \brief Retrieve logging string
     *
     * Retrives the currently logged string and clears the internally
     * buffered string to make way for another line of logs.  Only used by
     * mute::endl to output the line.  Will be replaced when a system for
     * handling logs are made.
     *
     * \todo Better system for outputting logs
     */
    std::string str();

    /**
     * \brief Set the source of the current logging message
     *
     * Sets the filename, line number, and function as the source of the log
     * message currently being created and returns the LoggingStream itself.
     *
     * \note For automatic insertion of these properties into the Mute
     *       application log stream, use the \ref MUTE_LOG macro.
     */
    LoggingStream& source(std::string file, int line, std::string function);

    /**
     * \brief Insert string into logging stream
     *
     * Places the provided \p string into the logging stream.  No extra
     * spaces will be inserted before or after the string.
     *
     * \return The \c LoggingStream opererated on, allowing multiple stream
     *         operations to be chained.
     */
    LoggingStream& operator<<(const std::string& string);

    /**
     * \brief Insert number into logging stream
     *
     * Places the provided \p number into the logging stream.  No extra
     * spaces will be inserted before or after the number.
     *
     * \return The \c LoggingStream opererated on, allowing multiple stream
     *         operations to be chained.
     */
    LoggingStream& operator<<(int number);
};

/**
 * \brief Execute logging stream manipulatior
 *
 * Calls \c f(*this)
 *
 * \return The \c LoggingStream opererated on, allowing multiple stream
 *         operations to be chained.
 */
LoggingStream& operator<<(LoggingStream&, LoggingStream& (*f)(LoggingStream&));

/**
 * \brief End current logging message
 *
 * Terminates the current logging message and sends it through the
 * logging system.  Messages are not sent before this manipulator is
 * applied to the logging stream, and sending newlines in the stream
 * should be avoided in favor of this unless the next line of content is
 * semantically connected with the previous one (e.g., a multiline
 * traceback.)
 *
 * \return The \c LoggingStream opererated on, allowing multiple stream
 *         operations to be chained.
 */
LoggingStream& endl(LoggingStream&);

/**
 * \brief Set log source of current message
 *
 * Set's the mute::log's source file/line/function to the line the macro
 * is invoked on.  The result of the macro expansion is a reference to
 * mute::log itself, meaning you can use this to both set the source of
 * the message and log the message in question at the same time.
 *
 * \par Example
 * \code
 * MUTE_LOG << "debug frobnicatior" << endl;
 * \endcode
 */
#define MUTE_LOG ::mute::log.source(__FILE__,__LINE__,__func__)

/**
 * \brief Application logging stream
 *
 * The logging stream used for logging in the application.  Similar in
 * in function and operaton to std::cout, but stores metadata of the
 * objects passed to it.
 *
 * \note The \ref MUTE_LOG macro should be prefered over directly
 *       referencing this object
 */
extern LoggingStream log;

/**
 * @} // defgroup logging
 */


} // namespace mute

#endif // MUTE_LOGGING_HPP
