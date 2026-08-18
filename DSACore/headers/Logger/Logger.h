#pragma once
#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
    #define DEBUG_MODE

    #include <cstdio>
    #include <string>
    #include <cstdarg>
    #include <vector>

    // Check if T has operator<< overloaded
    template<typename T, typename = void>
    struct has_ostream_operator : std::false_type {};

    // specialization that does have the operator<<
    template<typename T>
    struct has_ostream_operator<T, decltype(void(std::declval<std::ostream&>() << std::declval<T>()))> : std::true_type {};

    class Logger
    {
    public:
        Logger() = default;
        ~Logger() = default;

        static void LogTrace(const char* type, const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted(type, "TRACE", COLOR_WHITE, fmt, args);
            va_end(args);
        }
        static void LogDebug(const char* type, const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted(type, "DEBUG", COLOR_CYAN, fmt, args);
            va_end(args);
        }
        static void LogInfo(const char* type, const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted(type, "INFO", COLOR_GREEN, fmt, args);
            va_end(args);
        }
        static void LogWarn(const char* type, const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted(type, "WARNING", COLOR_YELLOW, fmt, args);
            va_end(args);
        }
        static void LogError(const char* type, const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted(type, "ERROR", COLOR_RED, fmt, args);
            va_end(args);
        }
        static void LogFatal(const char* type, const char* fmt, ...)
        {
            va_list args;
            va_start(args, fmt);
            logFormatted(type, "FATAL", COLOR_RED_BG_WHITE, fmt, args);
            va_end(args);
        }

    private:
        static inline void logFormatted(const char* type, const char* level, const char* color, const char* fmt, va_list args)
        {
            std::vector<char> buffer(1024);
            std::vsnprintf(buffer.data(), buffer.size(), fmt, args);
            log(type, level, buffer.data(), color);
        }
    
    private:
        static inline void log(const char* type, const char* level, const char* msg, const char* color)
        {
            // TODO: Time bug, its only time since start of program
            printf("%s", color);
            printf("(%s) [%s] %s: %s", __TIME__, type, level, msg);
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
        #define IS_STREAMABLE(Type) has_ostream_operator<Type>::value

        #ifndef DISABLE_TRACE
            #define LOG_TRACE(...) Logger::LogTrace("CORE", __VA_ARGS__)
            #define LOG_GUI_TRACE(...) Logger::LogTrace("GUI", __VA_ARGS__)
        #else
            #define LOG_TRACE(...)
            #define LOG_GUI_TRACE(...)
        #endif // DISABLE_TRACE
        #ifndef DISABLE_DEBUG
            #define LOG_DEBUG(...) Logger::LogDebug("CORE", __VA_ARGS__)
            #define LOG_GUI_DEBUG(...) Logger::LogDebug("GUI", __VA_ARGS__)
        #else
            #define LOG_DEBUG(...)
            #define LOG_GUI_DEBUG(...)
        #endif // DISABLE_DEBUG
        #ifndef DISABLE_INFO
            #define LOG_INFO(...) Logger::LogInfo("CORE", __VA_ARGS__)
            #define LOG_GUI_INFO(...) Logger::LogInfo("GUI", __VA_ARGS__)
        #else
            #define LOG_INFO(...)
            #define LOG_GUI_INFO(...)
        #endif // DISABLE_INFO
    #else
        #define IS_STREAMABLE(Type)

        #define LOG_TRACE(...)
        #define LOG_DEBUG(...)
        #define LOG_INFO(...)

        #define LOG_GUI_TRACE(...)
        #define LOG_GUI_DEBUG(...)
        #define LOG_GUI_INFO(...)
    #endif // DEBUG_MODE

    #ifndef DISABLE_WARN
        #define LOG_WARN(...) Logger::LogWarn("CORE", __VA_ARGS__)
        #define LOG_GUI_WARN(...) Logger::LogWarn("GUI", __VA_ARGS__)
    #else
        #define LOG_WARN(...)
        #define LOG_WARN(...)
    #endif // DISABLE_WARN
    #define LOG_ERROR(...) Logger::LogError("CORE", __VA_ARGS__)
    #define LOG_GUI_ERROR(...) Logger::LogError("GUI", __VA_ARGS__)
    #define LOG_FATAL(...) Logger::LogFatal("CORE", __VA_ARGS__)
    #define LOG_GUI_FATAL(...) Logger::LogFatal("GUI", __VA_ARGS__)

#else

    #define LOG_TRACE(...)
    #define LOG_DEBUG(...)
    #define LOG_INFO(...)
    #define LOG_WARN(...)
    #define LOG_ERROR(...)
    #define LOG_FATAL(...)

    #define LOG_GUI_TRACE(...)
    #define LOG_GUI_DEBUG(...)
    #define LOG_GUI_INFO(...)
    #define LOG_GUI_WARN(...)
    #define LOG_GUI_ERROR(...)
    #define LOG_GUI_FATAL(...)

#endif // ENABLE_LOGGING