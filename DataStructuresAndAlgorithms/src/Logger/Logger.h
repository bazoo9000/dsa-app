#pragma once
#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
    #define DEBUG_MODE

    #include <cstdio>

    class Logger
    {
    public:
        Logger() = default;
        ~Logger() = default;

        static void LogTrace(const char* msg)
        {
            log("TRACE", msg, COLOR_WHITE);
        }

        static void LogDebug(const char* msg)
        {
            log("DEBUG", msg, COLOR_CYAN);
        }

        static void LogInfo(const char* msg)
        {
            log("INFO", msg, COLOR_GREEN);
        }
        
        static void LogWarn(const char* msg)
        {
            log("WARNING", msg, COLOR_YELLOW);
        }
        
        static void LogError(const char* msg)
        {
            log("ERROR", msg, COLOR_RED);
        }
        
        static void LogFatal(const char* msg)
        {
            log("FATAL", msg, COLOR_RED_BG_WHITE);
        }

    private:
        static inline void log(const char* level, const char* msg, const char* color)
        {
            printf("%s %s ", color, __TIME__);
            printf("%s: %s", level, msg);
            printf("%s\n", COLOR_DEFAULT);
        }
        
    private:
        static constexpr const char* COLOR_RED = "\033[31m";
        static constexpr const char* COLOR_YELLOW = "\033[33m";
        static constexpr const char* COLOR_GREEN = "\033[32m";
        static constexpr const char* COLOR_CYAN = "\033[36m";
        static constexpr const char* COLOR_WHITE = "\033[37m";
        static constexpr const char* COLOR_RED_BG_WHITE = "\033[1;47;31m";
        static constexpr const char* COLOR_DEFAULT = "\033[0m"; // default color
    };

    #ifdef DEBUG_MODE
        #define LOG_TRACE(x)    Logger::LogTrace(x)
        #define LOG_DEBUG(x)    Logger::LogDebug(x)
        #define LOG_INFO(x)     Logger::LogInfo(x)
    #else
        #define LOG_TRACE(x)
        #define LOG_DEBUG(x)
        #define LOG_INFO(x)
    #endif // DEBUG_MODE

    #define LOG_WARN(x)     Logger::LogWarn(x)
    #define LOG_ERROR(x)    Logger::LogError(x)
    #define LOG_FATAL(x)    Logger::LogFatal(x)

#else

    #define LOG_TRACE(x)
    #define LOG_DEBUG(x)
    #define LOG_INFO(x)
    #define LOG_WARN(x)
    #define LOG_ERROR(x)
    #define LOG_FATAL(x)
    
#endif // ENABLE_LOGGING