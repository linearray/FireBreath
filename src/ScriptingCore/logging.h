/**********************************************************\ 
Original Author: Richard Bateman (taxilian)

Created:    Sep 30, 2010
License:    Dual license model; choose one of two:
            New BSD License
            http://www.opensource.org/licenses/bsd-license.php
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html
            
Copyright 2010 Facebook, Inc
\**********************************************************/

#pragma once
#ifndef H_FB_LOGGING
#define H_FB_LOGGING

#include <sstream>
#include <list>
#include <boost/preprocessor.hpp>

#if !FB_NO_LOGGING_MACROS
#  if defined(__GNUC__)
#    define FBLOG_FUNCTION() __PRETTY_FUNCTION__
#  elif defined(_MSC_VER)
#    define FBLOG_FUNCTION() __FUNCTION__
#  else
#    define FBLOG_FUNCTION() __func__
#  endif
#  define FBLOG_LOG_BODY(type, src, msg) \
    do { \
        std::ostringstream os; \
        os << msg; \
        FB::Log:: type (src, os.str(), __FILE__, __LINE__, FBLOG_FUNCTION()); \
    } while(0)
#endif

#if !FB_NO_LOGGING_MACROS
//#define NUMARGS(...) (sizeof((int[]){__VA_ARGS__})/sizeof(int))
#define NUMARGS(...) NUM_ARGS_HELPER(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...)    N

#define FBLOG_LOG2(src,msg,type) FBLOG_LOG_BODY(type,src,msg)
#define FBLOG_LOG1(msg,type)     FBLOG_LOG_BODY(type,"",msg)

#define GET_MACRO(...) \
    BOOST_PP_IF( \
        BOOST_PP_DEC( NUMARGS(__VA_ARGS__) ), \
        FBLOG_LOG2, \
        FBLOG_LOG1)

#define LP (
#define RP )
#define COMMA ,

# define FBLOG_TRACE(...) GET_MACRO (__VA_ARGS__) (__VA_ARGS__,trace)
# define FBLOG_DEBUG(...) GET_MACRO (__VA_ARGS__) (__VA_ARGS__,debug)
# define FBLOG_INFO(...)  GET_MACRO (__VA_ARGS__) (__VA_ARGS__,info)
# define FBLOG_WARN(...)  GET_MACRO (__VA_ARGS__) (__VA_ARGS__, warn)
# define FBLOG_ERROR(...) GET_MACRO (__VA_ARGS__) (__VA_ARGS__,error)
# define FBLOG_FATAL(...) GET_MACRO (__VA_ARGS__) (__VA_ARGS__,fatal)

/*#  define FBLOG_TRACE(...) CHOOSE(__VA_ARGS__)(trace,__VA_ARGS__)
#  define FBLOG_DEBUG(...) CHOOSE(__VA_ARGS__)(debug,__VA_ARGS__)
#  define FBLOG_INFO(...)  CHOOSE(__VA_ARGS__)(info,__VA_ARGS__)
#  define FBLOG_WARN(...)  CHOOSE(__VA_ARGS__)(warn,__VA_ARGS__)
#  define FBLOG_ERROR(...) CHOOSE(__VA_ARGS__)(error,__VA_ARGS__)
#  define FBLOG_FATAL(...) CHOOSE(__VA_ARGS__)(fatal,__VA_ARGS__)*/
#else
#  define FBLOG_TRACE(msg)
#  define FBLOG_DEBUG(msg)
#  define FBLOG_INFO(msg)
#  define FBLOG_WARN(msg)
#  define FBLOG_ERROR(msg)
#  define FBLOG_FATAL(msg)
#endif


namespace FB { namespace Log {

    void initLogging();
    void stopLogging();
    
    void trace(const std::string& src, const std::string& msg, const char *file, int line, const char *fn);
    void debug(const std::string& src, const std::string& msg, const char *file, int line, const char *fn);
    void  info(const std::string& src, const std::string& msg, const char *file, int line, const char *fn);
    void  warn(const std::string& src, const std::string& msg, const char *file, int line, const char *fn);
    void error(const std::string& src, const std::string& msg, const char *file, int line, const char *fn);
    void fatal(const std::string& src, const std::string& msg, const char *file, int line, const char *fn);

    //////////////////////////////////////////////////////////////////////////
    /// Used to specify the preferred loglevel for a logging system
    //////////////////////////////////////////////////////////////////////////
    enum LogLevel {
        // All log messages, no matter how small
        LogLevel_Trace  = 0x01,
        // Debug level log messages - messages you won't care about unless you're debugging
        LogLevel_Debug  = 0x02,
        // Informational log messages - not critical to know, but you might care
        LogLevel_Info   = 0x04,
        // Only log warning and worse messages
        LogLevel_Warn   = 0x08,
        // Only log messages that are actual errors
        LogLevel_Error  = 0x10
    };

    //////////////////////////////////////////////////////////////////////////
    /// @enum FB::Log::LogMethod
    /// 
    /// @brief Used to specify which logging methods should be enabled
    ///
    /// This enumeration is used by FB::FactoryBase::getLoggingMethods to
    /// specify the logging methods to enable. Currently Console and File
    /// are supported.
    //////////////////////////////////////////////////////////////////////////
    enum LogMethod {
        // Enable Console-mode logging (Debug console on windows, system console on other)
        LogMethod_Console  = 0x01,
        // Enable logging to a file - filename must be specified
        LogMethod_File  = 0x02
    };

    //////////////////////////////////////////////////////////////////////////    
    /// @brief Contains a list of log methods to enable
    ///
    /// This type is used by FB::FactoryBase::getLoggingMethods to
    /// return the logging methods to enable. Currently Console and File
    /// are supported. If File is desired, the string should contain the
    /// path and filename of the logfile. For console, the string is ignored
    //////////////////////////////////////////////////////////////////////////
    typedef std::list<std::pair<FB::Log::LogMethod, std::string> > LogMethodList;

}; };

#endif
