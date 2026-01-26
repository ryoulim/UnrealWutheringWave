@echo off
REM Unreal Engine 프로젝트 빠른 빌드 배치 파일
REM 더블클릭하거나 터미널에서 실행

set PROJECT_PATH=%~dp0WutheringWave.uproject
set ENGINE_PATH=C:\Program Files\Epic Games\UE_5.6\Engine

if not exist "%ENGINE_PATH%\Build\BatchFiles\Build.bat" (
    echo Unreal Engine 경로를 찾을 수 없습니다: %ENGINE_PATH%
    echo 배치 파일 내의 ENGINE_PATH 변수를 수정해주세요.
    pause
    exit /b 1
)

echo 빌드 시작...
echo 프로젝트: %PROJECT_PATH%
echo.

"%ENGINE_PATH%\Build\BatchFiles\Build.bat" WutheringWaveEditor Win64 Development "%PROJECT_PATH%" -WaitMutex -FromMsBuild

if %ERRORLEVEL% EQU 0 (
    echo.
    echo 빌드 성공!
    echo Unreal Editor에서 Ctrl+Alt+F11을 눌러 Live Coding을 사용하세요.
) else (
    echo.
    echo 빌드 실패! 오류를 확인하세요.
)

pause
