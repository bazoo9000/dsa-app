#pragma once
#define ENABLE_LOGGING
// #define USE_NEW_FORMATING // use new formatting for c++20

#if defined(_MSVC_LANG) && _MSVC_LANG >= 202002L
    #define CPP20
#elif __cplusplus >= 202002L
    #define CPP20
#endif

#ifdef ENABLE_LOGGING
    //#define DEBUG_MODE

    #include <cstdio>
    #include <string>
    #if defined(CPP20) && defined(USE_NEW_FORMATING)
        #include <format>
    #else
        #include <cstdarg>
        #include <vector>
    #endif

    class Logger
    {
    public:
        Logger() = default;
        ~Logger() = default;
        
        // this is for a formatted message
        #if defined(CPP20) && defined(USE_NEW_FORMATING)

        // using new format header from c++20
        static void LogTrace(std::string_view fmt, auto&&... args)
        {
            std::string str = std::format(fmt, std::forward<decltype(args)>(args)...);
            log("TRACE", str.c_str(), COLOR_WHITE);
        }
        static void LogDebug(std::string_view fmt, auto&&... args)
        {
            std::string str = std::format(fmt, std::forward<decltype(args)>(args)...);
            log("DEBUG", str.c_str(), COLOR_CYAN);
        }
        static void LogInfo(std::string_view fmt, auto&&... args)
        {
            std::string str = std::format(fmt, std::forward<decltype(args)>(args)...);
            log("INFO", str.c_str(), COLOR_GREEN);
        }
        static void LogWarn(std::string_view fmt, auto&&... args)
        {
            std::string str = std::format(fmt, std::forward<decltype(args)>(args)...);
            log("WARNING", str.c_str(), COLOR_YELLOW);
        }
        static void LogError(std::string_view fmt, auto&&... args)
        {
            std::string str = std::format(fmt, std::forward<decltype(args)>(args)...);
            log("ERROR", str.c_str(), COLOR_RED);
        }
        static void LogFatal(std::string_view fmt, auto&&... args)
        {
            std::string str = std::format(fmt, std::forward<decltype(args)>(args)...);
            log("FATAL", str.c_str(), COLOR_RED_BG_WHITE);
        }
        
        #else // NEW_FORMATING ^^^

        // using old c style formatting
        static void LogTrace(const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted("TRACE", COLOR_WHITE, fmt, args);
            va_end(args);
        }
        static void LogDebug(const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted("DEBUG", COLOR_CYAN, fmt, args);
            va_end(args);
        }
        static void LogInfo(const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted("INFO", COLOR_GREEN, fmt, args);
            va_end(args);
        }
        static void LogWarn(const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted("WARNING", COLOR_YELLOW, fmt, args);
            va_end(args);
        }
        static void LogError(const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted("ERROR", COLOR_RED, fmt, args);
            va_end(args);
        }
        static void LogFatal(const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted("FATAL", COLOR_RED_BG_WHITE, fmt, args);
            va_end(args);
        }

    private:
        static inline void logFormatted(const char* level, const char* color, const char* fmt, va_list args)
        {
            std::vector<char> buffer(1024);
            std::vsnprintf(buffer.data(), buffer.size(), fmt, args);
            log(level, buffer.data(), color);
        }

        #endif // OLD_FORMATING ^^^
    
    private:
        static inline void log(const char* level, const char* msg, const char* color)
        {
            printf("%s %s ", color, __TIME__);
            printf("%s: %s", level, msg);
            printf("%s\n", COLOR_DEFAULT_RESET);
        }
        
    private:
        static constexpr const char* COLOR_RED = "\033[31m";
        static constexpr const char* COLOR_YELLOW = "\033[33m";
        static constexpr const char* COLOR_GREEN = "\033[32m";
        static constexpr const char* COLOR_CYAN = "\033[36m";
        static constexpr const char* COLOR_WHITE = "\033[37m";
        static constexpr const char* COLOR_RED_BG_WHITE = "\033[1;47;31m";
        static constexpr const char* COLOR_DEFAULT_RESET = "\033[0m"; // default color
    };

    #ifdef DEBUG_MODE
        #ifndef DISABLE_TRACE
            #define LOG_TRACE(x, ...) Logger::LogTrace(x, __VA_ARGS__)
        #else
            #define LOG_TRACE(x, ...)
        #endif // DISABLE_TRACE
        #ifndef DISABLE_DEBUG
            #define LOG_DEBUG(x, ...) Logger::LogDebug(x, __VA_ARGS__)
        #else
            #define LOG_DEBUG(x, ...)
        #endif // DISABLE_DEBUG
        #ifndef DISABLE_INFO
            #define LOG_INFO(x, ...) Logger::LogInfo(x, __VA_ARGS__)
        #else
            #define LOG_INFO(x, ...)
        #endif // DISABLE_INFO
    #else
        #define LOG_TRACE(x, ...)
        #define LOG_DEBUG(x, ...)
        #define LOG_INFO(x, ...)
    #endif // DEBUG_MODE

    #ifndef DISABLE_WARN
        #define LOG_WARN(x, ...) Logger::LogWarn(x, __VA_ARGS__)
    #else
        #define LOG_WARN(x, ...)
    #endif // DISABLE_WARN
    #define LOG_ERROR(x, ...) Logger::LogError(x, __VA_ARGS__)
    #define LOG_FATAL(x, ...) Logger::LogFatal(x, __VA_ARGS__)

#else

    #define LOG_TRACE(x, ...)
    #define LOG_DEBUG(x, ...)
    #define LOG_INFO(x, ...)
    #define LOG_WARN(x, ...)
    #define LOG_ERROR(x, ...)
    #define LOG_FATAL(x, ...)

#endif // ENABLE_LOGGING