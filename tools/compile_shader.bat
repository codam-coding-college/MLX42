:: -----------------------------------------------------------------------------
:: Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
:: See README in the root project for more information.
:: -----------------------------------------------------------------------------

@echo off
SETLOCAL DisableDelayedExpansion

:: go to usage function if no arguments have been given to the script
IF [%1]==[] GOTO usage

:: check if input file exists before continuing
IF NOT EXIST %1 GOTO fnotfound

SET SHADERTYPE=%~x1
SET SHADERTYPE=%SHADERTYPE:~1%

echo // -----------------------------------------------------------------------------
echo // Codam Coding College, Amsterdam @ <2022-2023> by W2Wizard.
echo // See README in the root project for more information.
echo // -----------------------------------------------------------------------------
echo.
echo // If you wish to modify this file edit the .vert or .frag file!
echo.
echo #include "MLX42/MLX42_Int.h"
echo.

FOR /F "delims=" %%A IN (%1) DO IF NOT DEFINED VERSIONLINE set "VERSIONLINE=%%A"
echo const char* %SHADERTYPE%_shader = "%VERSIONLINE%\n"
FOR /F "skip=1 delims=" %%A IN (%1) DO (
	IF "%%A" == "}" (echo 	"%%A";) ELSE (echo 	"%%A")
)

ENDLOCAL
EXIT /B 0

:: usage function exits the script with exit code 3 (path not found)
:usage
echo ERROR: missing arguments, use as follows: %0 ^<ShaderFile^> 1>&2
ENDLOCAL
EXIT /B 3

:: fnotfound function exits the script with exit code 2 (file not found)
:fnotfound
echo ERROR: shader file not found: %1 1>&2
ENDLOCAL
EXIT /B 2
