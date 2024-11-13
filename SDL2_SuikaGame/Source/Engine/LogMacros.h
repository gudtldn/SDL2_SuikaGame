#pragma once
#ifdef NDEBUG

#define LOG_INFO(fmt, ...)
#define LOG_WARN(fmt, ...)
#define LOG_ERROR(fmt, ...)
#define LOG_CRITICAL(fmt, ...)
#define LOG_DEBUG(fmt, ...)
#define LOG_VERBOSE(fmt, ...)

#else

static consteval const char* filename(const char* path) {
    const char* file = path;
    while (*path) {
        if (*path == '/' || *path == '\\') {
            file = path + 1;
        }
        path++;
    }
    return file;
}

#define __FILENAME__ filename(__FILE__)
#define __LOG__(func, fmt, ...)    func(SDL_LOG_CATEGORY_APPLICATION, "[%s:%d] %s", __FILENAME__, __LINE__, std::format(fmt "\n", __VA_ARGS__).c_str())

#define LOG_INFO(fmt, ...)         __LOG__(SDL_LogInfo, fmt, __VA_ARGS__)      // 일반적인 정보
#define LOG_WARN(fmt, ...)         __LOG__(SDL_LogWarn, fmt, __VA_ARGS__)      // 경고
#define LOG_ERROR(fmt, ...)        __LOG__(SDL_LogError, fmt, __VA_ARGS__)     // 에러
#define LOG_CRITICAL(fmt, ...)     __LOG__(SDL_LogCritical, fmt, __VA_ARGS__)  // 치명적인 에러
#define LOG_DEBUG(fmt, ...)        __LOG__(SDL_LogDebug, fmt, __VA_ARGS__)     // 디버그
#define LOG_VERBOSE(fmt, ...)      __LOG__(SDL_LogVerbose, fmt, __VA_ARGS__)   // 상세 정보

#endif // DEBUG
