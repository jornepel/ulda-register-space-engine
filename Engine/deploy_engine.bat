@echo off
:: ============================================================================
:: deploy_engine.bat — Direct3D 11 Proxy DLL Automated Deployment Script
:: Enforces administrative privileges to target local sandbox directories.
:: ============================================================================

echo ====================================================================
echo  DEPLOYMENT PIPELINE — ℤ[φ]³ TOPOLOGICAL ENGINE AUTOMATED INJECTOR
echo ====================================================================
echo.

:: 1. Administrative Privileges Verification Gate
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo [ CRITICAL WARNING ] Administrative validation failed.
    echo                      Please right-click this batch file and select
    echo                      "Run as Administrator" to authorize deployment.
    echo.
    pause
    exit /b 1
)

:: 2. Local Proxy Binary Verification
if not exist "d3d11.dll" (
    echo [ ERROR ] Local proxy hook binary 'd3d11.dll' not found in workspace.
    echo           Please run 'run_all.sh' or execute 'make proxy' via MinGW64.
    echo.
    pause
    exit /b 1
)

:: 3. Target Path Input Extraction
set /p TARGET_DIR="Enter the absolute path of the target application directory: "

:: Strip wrapping quotation characters from the raw user string buffer
set TARGET_DIR=%TARGET_DIR:"=%

if not exist "%TARGET_DIR%" (
    echo [ ERROR ] Destination directory path is unresolvable or invalid.
    echo.
    pause
    exit /b 1
)

echo.
echo [ STATUS ] Destination verified: "%TARGET_DIR%"
echo [ STATUS ] Shunting custom topological d3d11 proxy library...

:: 4. Direct Resource Injection
copy /y "d3d11.dll" "%TARGET_DIR%\d3d11.dll"

if %errorLevel% equ 0 (
    echo.
    echo ====================================================================
    echo [ PASS SUCCESS ] Proxy library successfully injected into target path.
    echo                  The Tensor Shear Shunts are active on the host path.
    echo ====================================================================
) else (
    echo [ CRITICAL ERROR ] Copy pass failed. Verify system directory write permissions.
)

echo.
pause
