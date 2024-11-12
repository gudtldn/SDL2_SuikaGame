#pragma once


/// @brief SDL 초기화를 담당하는 매니저 클래스
class SDLManager
{
public:
    /// @brief 기본적인 SDL 초기화를 수행합니다.
    /// @exception std::runtime_error SDL 초기화에 실패한 경우
    SDLManager();

    /// @brief 사용한 자원을 해제합니다.
    ~SDLManager();
};
