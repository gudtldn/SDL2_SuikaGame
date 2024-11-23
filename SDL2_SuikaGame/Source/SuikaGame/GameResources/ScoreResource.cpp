#include "ScoreResource.h"
#include <fstream>
#include <Windows.h>

namespace fs = std::filesystem;


ScoreResource::ScoreResource()
{
    // .exe 파일의 절대 경로 가져오기
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    save_file_path = fs::path(path).parent_path() / "SuikaGameData.bin";
}

void ScoreResource::Load()
{
    // TODO: 나중에 SavefileResource 만들어서 저장이 필요한 리소스들을 한번에 저장하도록 수정
    // 세이브 파일 로드
    LoadFromFile();
}

void ScoreResource::LoadFromFile()
{
    LOG_INFO("Loading from file");

    std::ifstream file { save_file_path, std::ios::binary };
    if (file.is_open())
    {
        file.read(reinterpret_cast<char*>(&high_score), sizeof(high_score));
        file.close();
    }
    else
    {
        LOG_INFO("No existing save file found. Starting with default high score.");
        return;
    }

    LOG_INFO("Loaded from file");
}

void ScoreResource::SaveToFile()
{
    LOG_INFO("Saving to file...");

    std::ofstream file { save_file_path, std::ios::binary };
    if (file.is_open())
    {
        file.write(reinterpret_cast<char*>(&high_score), sizeof(high_score));
        file.close();
    }
    else
    {
        LOG_ERROR("Failed to save to file");
        return;
    }

    LOG_INFO("Saved to file");
}
