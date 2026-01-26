# Unreal Engine 프로젝트 빠른 빌드 스크립트
# 사용법: .\QuickBuild.ps1

$ProjectPath = "C:\UnrealProject\WutheringWave\WutheringWave.uproject"
$EnginePath = "C:\Program Files\Epic Games\UE_5.6\Engine"

# Unreal Engine 경로 확인
if (-not (Test-Path $EnginePath)) {
    Write-Host "Unreal Engine 경로를 찾을 수 없습니다: $EnginePath" -ForegroundColor Red
    Write-Host "스크립트 내의 EnginePath 변수를 수정해주세요." -ForegroundColor Yellow
    exit 1
}

$BuildScript = Join-Path $EnginePath "Build\BatchFiles\Build.bat"

Write-Host "빌드 시작..." -ForegroundColor Green
Write-Host "프로젝트: $ProjectPath" -ForegroundColor Cyan
Write-Host ""

# 에디터 빌드 (Development)
& $BuildScript WutheringWaveEditor Win64 Development $ProjectPath -WaitMutex -FromMsBuild

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "빌드 성공!" -ForegroundColor Green
    Write-Host "Unreal Editor에서 Ctrl+Alt+F11을 눌러 Live Coding을 사용하세요." -ForegroundColor Yellow
} else {
    Write-Host ""
    Write-Host "빌드 실패! 오류를 확인하세요." -ForegroundColor Red
    exit $LASTEXITCODE
}
