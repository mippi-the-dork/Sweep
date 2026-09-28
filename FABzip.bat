@echo off
setlocal EnableExtensions

REM ============================================================
REM Unreal Engine Plugin Packager
REM Creates <PluginFolderName>.zip beside this BAT file.
REM ============================================================

REM Always work from the folder containing this BAT file.
pushd "%~dp0"

REM Get the current folder name for the ZIP filename.
for %%I in ("%CD%") do set "FolderName=%%~nxI"

set "ZipPath=%CD%\%FolderName%.zip"
set "TempDir=%TEMP%\UEPluginPackage_%FolderName%_%RANDOM%_%RANDOM%"

echo.
echo Packaging: %FolderName%
echo.

REM Delete the previous ZIP if one already exists.
if exist "%ZipPath%" (
    echo Deleting previous archive...
    del /F /Q "%ZipPath%"
    if exist "%ZipPath%" (
        echo.
        echo ERROR: Could not delete:
        echo "%ZipPath%"
        goto :error
    )
)

REM Create a temporary staging folder.
mkdir "%TempDir%" >nul 2>&1
if errorlevel 1 (
    echo.
    echo ERROR: Could not create temporary staging folder:
    echo "%TempDir%"
    goto :error
)

echo Copying release files...

REM Copy the plugin while excluding:
REM   - Any file or folder beginning with "."
REM   - Binaries
REM   - Intermediate
REM   - Saved
REM   - LICENSE and LICENSE.*
REM   - All .bat files
REM
REM Robocopy exit codes 0-7 are successful. 8+ are failures.
robocopy "%CD%" "%TempDir%" /E /R:0 /W:0 /NFL /NDL /NJH /NJS /NP ^
    /XD "Binaries" "Intermediate" "Saved" ".*" ^
    /XF ".*" "LICENSE" "LICENSE.*" "*.bat"

set "RoboCode=%ERRORLEVEL%"

if %RoboCode% GEQ 8 (
    echo.
    echo ERROR: Robocopy failed with exit code %RoboCode%.
    goto :cleanup_error
)

echo Creating ZIP...

powershell.exe -NoProfile -ExecutionPolicy Bypass -Command ^
    "Compress-Archive -Path '%TempDir%\*' -DestinationPath '%ZipPath%' -CompressionLevel Optimal -Force"

if errorlevel 1 (
    echo.
    echo ERROR: ZIP creation failed.
    goto :cleanup_error
)

REM Remove temporary staging files.
rmdir /S /Q "%TempDir%" >nul 2>&1

echo.
echo ============================================================
echo SUCCESS
echo Created:
echo "%ZipPath%"
echo ============================================================
echo.

popd
pause
exit /b 0

:cleanup_error
rmdir /S /Q "%TempDir%" >nul 2>&1

:error
echo.
echo Packaging failed.
echo.
popd
pause
exit /b 1
