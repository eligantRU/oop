@ECHO OFF

set PROGRAM="%~1"

REM No params
CALL %PROGRAM% 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\err.txt
ECHO Test "no params" SUCCEED 

REM Reverse(-1) 
CALL %PROGRAM% -1 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correct-1.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\err.txt
ECHO Test "Reverse(-1)" SUCCEED 

REM Reverse(270) 
CALL %PROGRAM% 270 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correct270.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\err.txt
ECHO Test "Reverse(270)" SUCCEED 

REM Reverse("f") 
CALL %PROGRAM% "f" 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctF.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\err.txt
ECHO Test "Reverse("f")" SUCCEED 

REM Reverse(6) = 96
CALL %PROGRAM% 6 > %TEMP%\reverse6.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\reverse6.txt correctTest\correctReverse6.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\reverse6.txt
ECHO Test "Reverse(6) = 96" SUCCEED

REM Reverse(128) = 1
CALL %PROGRAM% 128 > %TEMP%\reverse128.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\reverse128.txt correctTest\correctReverse128.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\reverse128.txt
ECHO Test "Reverse(128) = 1" SUCCEED

REM Reverse(1) = 128
CALL %PROGRAM% 1 > %TEMP%\reverse1.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\reverse1.txt correctTest\correctReverse1.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\reverse1.txt
ECHO Test "Reverse(1) = 128" SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:err
ECHO TEST FAILED
EXIT 1
