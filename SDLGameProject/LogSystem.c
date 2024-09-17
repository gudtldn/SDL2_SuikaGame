#define _CRT_SECURE_NO_WARNINGS

#include "LogSystem.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//~기본 로그 카테고리 정의
DEFINE_LOG_CATEGORY(LogTemp);
//~기본 로그 카테고리 정의

static ELogVerbosity g_LogLevel = Debug;
static bool g_bLogToFile = false;
static FILE* g_LogFile = NULL;
static char g_LogFormat[256] = "[%s] [%s] %s (%s:%d): %s";

const char* GetLogVerbosityToString(ELogVerbosity Verbosity)
{
    switch (Verbosity)
    {
    case Fatal:
        return "Fatal";
    case Error:
        return "Error";
    case Warning:
        return "Warning";
    case Info:
        return "Info";
    case Debug:
        return "Debug";
    default:
        return "Unknown";
    }
}

ELogVerbosity GetLogVerbosityFromString(const char* Verbosity)
{
    if (strcmp(Verbosity, "Fatal") == 0)
    {
        return Fatal;
    }
    else if (strcmp(Verbosity, "Error") == 0)
    {
        return Error;
    }
    else if (strcmp(Verbosity, "Warning") == 0)
    {
        return Warning;
    }
    else if (strcmp(Verbosity, "Info") == 0)
    {
        return Info;
    }
    else if (strcmp(Verbosity, "Debug") == 0)
    {
        return Debug;
    }
    else
    {
        return Unknown;
    }
}

void LogMessage(const char* Category, ELogVerbosity Verbosity, const char* File, int Line, const char* Format, ...)
{
    if (Verbosity > g_LogLevel) return;

    // 현재 시간 문자열로 변환
    time_t Now = time(NULL);
    char TimeString[26];
    ctime_s(TimeString, sizeof(TimeString), &Now);
    TimeString[24] = '\0';  // 개행 문자 제거

    // 로그 메시지 생성
    char Buffer[1024];
    va_list Args;
    va_start(Args, Format);
    int Written = vsnprintf(Buffer, sizeof(Buffer), Format, Args);
    va_end(Args);

    if (Written < 0 || Written >= sizeof(Buffer)) {
        // 오류 처리 또는 로그 메시지 잘라내기
        Buffer[sizeof(Buffer) - 1] = '\0';
    }

    // 출력할 로그 메시지 생성
    char ResultMessage[2048];
    Written = snprintf(
        ResultMessage,
        sizeof(ResultMessage),
        g_LogFormat,
        TimeString,
        GetLogVerbosityToString(Verbosity),
        Category, File, Line, Buffer
    );

    if (Written < 0 || Written >= sizeof(ResultMessage)) {
        // 오류 처리 또는 로그 메시지 잘라내기
        ResultMessage[sizeof(ResultMessage) - 1] = '\0';
    }

    // 로그 출력
    if (g_bLogToFile && g_LogFile)
    {
        if (fprintf(g_LogFile, "%s", ResultMessage) < 0) {
            // 파일 쓰기 오류 처리
            perror("Error writing to log file");
        }
        fflush(g_LogFile);
    }
    printf("%s", ResultMessage);
}

void SetLogLevel(ELogVerbosity Level)
{
    g_LogLevel = Level;
}

void SetLogToFile(bool bToFile, const char* OutputFile)
{
    if (g_LogFile)
    {
        fclose(g_LogFile);
        g_LogFile = NULL;
    }

    g_bLogToFile = bToFile;
    if (bToFile)
    {
        g_LogFile = fopen(OutputFile, "a");
        if (!g_LogFile) {
            perror("Error opening log file");
            g_bLogToFile = false;
        }
    }
}

void SetLogFormat(const char* format)
{
    strncpy(g_LogFormat, format, sizeof(g_LogFormat));
    g_LogFormat[sizeof(g_LogFormat) - 1] = '\0';
}

#undef _CRT_SECURE_NO_WARNINGS
