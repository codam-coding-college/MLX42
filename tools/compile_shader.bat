:: -----------------------------------------------------------------------------
:: Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
:: See README in the root project for more information.
:: -----------------------------------------------------------------------------

@echo off
SETLOCAL EnableDelayedExpansion

:: Go to usage function if no arguments have been given to the script
IF [%1]==[] GOTO usage

:: Check if input file exists before continuing
IF NOT EXIST %1 GOTO fnotfound

SET SHADERTYPE=%~x1
SET SHADERTYPE=%SHADERTYPE:~1%

echo // -----------------------------------------------------------------------------
echo // Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
echo // See README in the root project for more information.
echo // -----------------------------------------------------------------------------
echo.
echo // If you wish to modify this file edit the .vert or .frag file!
echo.
echo #include "MLX42/MLX42_Int.h"
echo.

REM Read the shader version line
SET VERSIONLINE=
FOR /F "delims=" %%A IN (%1) DO (
    IF NOT DEFINED VERSIONLINE (
        SET VERSIONLINE=%%A
        SET "FIRSTLINE=1"
    ) ELSE (
        IF !FIRSTLINE! NEQ 1 (
            IF "%%A" == "}" (
                echo     "%%A";
            ) ELSE (
                echo     "%%A"
            )
        )
    )
)

REM Output the shader declaration
IF "%2"=="1" (
    echo const char* %SHADERTYPE%_shader = "#version 300 es\n"
    IF /I "%SHADERTYPE%"=="frag" (
        echo     "precision mediump float;\n"
    )
) ELSE (
    echo const char* %SHADERTYPE%_shader = "%VERSIONLINE%\n"
)

ENDLOCAL
EXIT /B 0

:: usage function exits the script with exit code 3 (missing arguments)
:usage
echo ERROR: missing arguments, use as follows: %0 ^<ShaderFile^> ^<Mode^> 1>&2
ENDLOCAL
EXIT /B 3

:: fnotfound function exits the script with exit code 2 (file not found)
:fnotfound
echo ERROR: shader file not found: %1 1>&2
ENDLOCAL
EXIT /B 2
