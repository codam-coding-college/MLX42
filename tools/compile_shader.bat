:: -----------------------------------------------------------------------------
:: Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
:: See README in the root project for more information.
:: -----------------------------------------------------------------------------

@echo off
SETLOCAL EnableDelayedExpansion

:: If no arguments have been given to the script
IF "%~1"=="" (
    echo ERROR: missing arguments, use as follows: %~nx0 ^<ShaderFile^> ^<Mode^> 1>&2
    ENDLOCAL
    EXIT /B 1
)

:: Check if file exists
IF NOT EXIST "%~1" (
    echo ERROR: shader file not found: %~1 1>&2
    ENDLOCAL
    EXIT /B 2
)

:: Extract the shader type (file extension without the dot)
SET "SHADERTYPE=%~x1"
SET "SHADERTYPE=%SHADERTYPE:~1%"

echo // -----------------------------------------------------------------------------
echo // Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
echo // See README in the root project for more information.
echo // -----------------------------------------------------------------------------
echo.
echo // If you wish to modify this file edit the .vert or .frag file!
echo.
echo #include "MLX42/MLX42_Int.h"
echo.

:: Check the Mode argument (WASM specific output if Mode == 1)
IF "%~2"=="1" (
    echo const char* %SHADERTYPE%_shader = "#version 300 es\n"
    echo     "precision mediump float;\n"
) ELSE (
    FOR /F "delims=" %%A IN ('more +0 "%~1"') DO (
        echo const char* %SHADERTYPE%_shader = "%%A\n"
        GOTO next
    )
)

:next
:: Read and process the rest of the shader file
FOR /F "usebackq delims=" %%A IN ("%~1") DO (
    IF NOT "%%A"=="" (
        IF "%%A"=="}" (
            echo     "%%A";
        ) ELSE (
            echo     "%%A"
        )
    )
)

ENDLOCAL
EXIT /B 0
