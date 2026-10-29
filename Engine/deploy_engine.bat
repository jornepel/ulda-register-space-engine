@echo off
:: ========================================================================
:: deploy_engine.bat — Automated ULDA Engine Deployment Wrapper for Gamers
:: ========================================================================
cls
echo ====================================================================
echo     ULDA SYSTEM DEPLOYMENT PROTOCOL | Production-Grade Installer   
echo ====================================================================
echo.

:: 1. Administrative privilege validation check
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo [✗] Error: This deployment script requires Administrative privileges.
    echo     Please right-click deploy_engine.bat and select 'Run as administrator'.
    echo.
    pause
    exit /b 1
)

echo [✓] Administrative clearance granted.
echo [✓] Verifying local binary components...

:: 2. Cross-verify compiled asset availability
if not exist "emu.exe" (
    echo [✗] Error: emu.exe missing from workspace. Build the engine first.
    pause
    exit /b 1
)
if not exist "d3d11.dll" (
    echo [✗] Error: d3d11.dll missing from workspace. Build the engine first.
    pause
    exit /b 1
)

echo [✓] All silicon assets verified.
echo.
echo --------------------------------------------------------------------
echo   TARGET SELECTION: Specify the directory of the game to hook
echo   (e.g., C:\Program Files (x86)\Steam\steamapps\common\TargetGame)
echo --------------------------------------------------------------------
echo.

set /p GAME_DIR="Enter Target Game Executable Path: "

if not exist "%GAME_DIR%" (
    echo.
    echo [✗] Error: Specified game path does not exist. Installation aborted.
    pause
    exit /b 1
)

echo.
echo [Deploying] Copying proxy injectors into game process tree...

:: 3. Inject the compiled d3d11.dll wrapper right next to the game's main executable
copy /y "d3d11.dll" "%GAME_DIR%\d3d11.dll" >nul
if %errorLevel% neq 0 (
    echo [✗] Error: Failed to write proxy wrapper to target folder. Check file locks.
    pause
    exit /b 1
)

:: 4. Inject the independent telemetry monitor binary for live gamer diagnostics
copy /y "emu.exe" "%GAME_DIR%\ulda_emu.exe" >nul

echo [✓] Proxy attachment complete: d3d11.dll linked into target runtime.
echo.
echo ====================================================================
echo [✓] DEPLOYMENT COMPLETE: All channels successfully shunted!
echo     Launch the game. The engine will intercept coordinates live.
echo ====================================================================
echo.
pause