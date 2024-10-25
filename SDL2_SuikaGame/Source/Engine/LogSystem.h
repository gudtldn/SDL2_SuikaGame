#pragma once
#include <stdbool.h>

#ifdef NDEBUG
#define LOG(CategoryName, Verbosity, Format, ...)

#define LOG_FATAL(CategoryName, Format, ...)
#define LOG_ERROR(CategoryName, Format, ...)
#define LOG_WARNING(CategoryName, Format, ...)
#define LOG_INFO(CategoryName, Format, ...)
#define LOG_DEBUG(CategoryName, Format, ...)

#define DEBUG_VALUE(Identifier, Value)
#else
#include <string.h>
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOG(CategoryName, Verbosity, Format, ...) \
    do { \
        LogMessage(CategoryName, Verbosity, __FILENAME__, __LINE__, Format, ##__VA_ARGS__); \
    } while(0)

#define LOG_FATAL(CategoryName, Format, ...) LOG(CategoryName, Fatal, Format, ##__VA_ARGS__)
#define LOG_ERROR(CategoryName, Format, ...) LOG(CategoryName, Error, Format, ##__VA_ARGS__)
#define LOG_WARNING(CategoryName, Format, ...) LOG(CategoryName, Warning, Format, ##__VA_ARGS__)
#define LOG_INFO(CategoryName, Format, ...) LOG(CategoryName, Info, Format, ##__VA_ARGS__)
#define LOG_DEBUG(CategoryName, Format, ...) LOG(CategoryName, Debug, Format, ##__VA_ARGS__)

#define DEBUG_VALUE(TypeFormat, Identifier) LOG_DEBUG(LogDebugValue, "[%s:%d] %s = %" #TypeFormat, __FILENAME__, __LINE__, #Identifier, Identifier)
#endif


// 로그 카테고리 선언
#define DECLARE_LOG_CATEGORY_EXTERN(CategoryName) \
    extern const char* CategoryName;

// 로그 카테고리 정의
#define DEFINE_LOG_CATEGORY(CategoryName) \
    const char* CategoryName = #CategoryName;


//~기본 로그 카테고리 선언
DECLARE_LOG_CATEGORY_EXTERN(LogTemp);
DECLARE_LOG_CATEGORY_EXTERN(LogDebugValue);
//~기본 로그 카테고리 선언


/// @brief 로그 수준
typedef enum ELogVerbosity
{
    // 치명적 오류
    Fatal,

    // 일반적인 오류
    Error,

    // 경고
    Warning,

    // 정보
    Info,

    // 디버그
    Debug,

    // 알 수 없음
    Unknown
} ELogVerbosity;

/// @brief 로그 수준을 문자열로 변환
/// @param Verbosity 로그 수준
/// @return 변환된 문자열
const char* GetLogVerbosityToString(ELogVerbosity Verbosity);

/// @brief 문자열을 로그 수준으로 변환
/// @param Verbosity 로그 수준 문자열
/// @return ELogVerbosity
ELogVerbosity GetLogVerbosityFromString(const char* Verbosity);

/// @brief 로그 메시지 출력
/// @param Category 로그 카테고리
/// @param Verbosity 로그 수준
/// @param File 현재파일 이름
/// @param Line 현재 라인 번호
/// @param Format 로그 형식
/// @param ... 가변인자
void LogMessage(const char* Category, ELogVerbosity Verbosity, const char* File, int Line, const char* Format, ...);

/// @brief 로그 수준 설정
/// @param Level 로그 수준
void SetLogLevel(ELogVerbosity Level);

/// @brief 파일에 로그를 출력할지 여부 설정
/// @param bToFile 파일에 로그를 출력할지 여부 (true: 파일에 출력, false: 콘솔에 출력)
/// @param Filename 파일 이름
void SetLogToFile(bool bToFile, const char* Filename);

/// @brief 로그 형식 설정
/// @param Format 로그 형식
void SetLogFormat(const char* Format);
