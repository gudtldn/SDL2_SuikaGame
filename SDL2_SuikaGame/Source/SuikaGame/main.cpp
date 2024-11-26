#include "EnginePCH.h"
#include "SuikaGame/Stages/MenuStage.h"
#include "SuikaGame/GameResources/FruitResource.h"
#include "SuikaGame/GameResources/ScoreResource.h"
#include "SuikaGame/GameResources/TempScreenCaptureResource.h"
#include "SuikaGame/GameObjects/BackgroundObject.h"
#include "SuikaGame/GameObjects/BgmObject.h"

#include <windows.h>
#include <dbghelp.h>


// https://lazyfoo.net/tutorials/SDL/index.php
// https://www.youtube.com/watch?v=BDqJUJ-jOSQ
// https://box2d.org/documentation/hello.html
// https://wikidocs.net/book/6636

namespace
{
// 메세지 박스 띄우기
void ShowMessageBox(const std::string& message)
{
    // WCHAR 배열을 위한 버퍼
    WCHAR error_message[256];

    // ANSI 문자열을 WCHAR로 변환
    MultiByteToWideChar(
        CP_UTF8,
        0,
        message.c_str(),
        -1,
        error_message,
        sizeof(error_message) / sizeof(WCHAR)
    );

    // 메세지 박스 띄우기
    MessageBoxW(nullptr, error_message, L"Error", MB_OK | MB_ICONERROR);
}

// 예외 처리기 및 메모리 덤프 생성
LONG WINAPI ExceptionCallBack(EXCEPTION_POINTERS* exceptionInfo)
{
	MINIDUMP_EXCEPTION_INFORMATION info {
		.ThreadId = GetCurrentThreadId(),
		.ExceptionPointers = exceptionInfo,
		.ClientPointers = false
	};

	const std::wstring stamp(L"crash.dmp");
	const HANDLE hFile = CreateFileW(
	    stamp.c_str(),
	    GENERIC_WRITE,
	    FILE_SHARE_WRITE,
	    nullptr,
	    CREATE_ALWAYS,
	    FILE_ATTRIBUTE_NORMAL,
	    nullptr
	);

#ifdef _DEBUG
	constexpr DWORD flags = MiniDumpWithFullMemory
						| MiniDumpWithFullMemoryInfo
						| MiniDumpWithHandleData
						| MiniDumpWithUnloadedModules
						| MiniDumpWithThreadInfo;
#else
    constexpr DWORD flags = MiniDumpNormal;
#endif

	// 위에서 받은 내용들을 토대로 덤프 파일을 만든다.
	MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		hFile,
		static_cast<MINIDUMP_TYPE>(flags),
		&info,
		nullptr,
		nullptr
	);
    CloseHandle(hFile);

    ShowMessageBox("An error occurred. The program will be terminated.");
	return 0L;
}

}

int main(int argc, char* args[])
{
#if _DEBUG
    // Debug 모드일 때 로그 레벨을 Debug로 설정
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

    // 예외 처리기 등록
    SetUnhandledExceptionFilter(ExceptionCallBack);

    try
    {
        // SDL 관리자 생성
        SDLManager sdl_manager{};
    	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        // Engine 생성
        GameEngine engine = GameEngine{
            "Suika Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT
        };

        // Engine 실행
        engine.SetStage<MenuStage>();
        engine.GetResourceManager().AddResource<FruitResource>();
        engine.GetResourceManager().AddResource<ScoreResource>();
        engine.GetResourceManager().AddResource<TempScreenCaptureResource>();
        engine.GetObjectManager().CreateGameObject<BackgroundObject>();
        engine.GetObjectManager().CreateGameObject<BgmObject>();
        engine.Run();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("An error occurred: {}", e.what());
        ShowMessageBox(e.what());
        return -1;
    }

    return 0;
}
