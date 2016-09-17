@ECHO OFF

set PROGRAM="%~1"

REM Reverse(6) = 96
%PROGRAM% 6 > %TEMP%\reverse6.txt
IF ERRORLEVEL 1 GOTO err
FC %TEMP%\reverse6.txt correctTest\correctReverse6.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\reverse6.txt
ECHO Test "Reverse(6) = 96" SUCCEED

REM Reverse(128) = 1
%PROGRAM% 128 > %TEMP%\reverse128.txt
IF ERRORLEVEL 1 GOTO err
FC %TEMP%\reverse128.txt correctTest\correctReverse128.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\reverse128.txt
ECHO Test "Reverse(128) = 1" SUCCEED

REM Reverse(1) = 128
%PROGRAM% 1 > %TEMP%\reverse1.txt
IF ERRORLEVEL 1 GOTO err
FC %TEMP%\reverse1.txt correctTest\correctReverse1.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\reverse1.txt
ECHO Test "Reverse(1) = 128" SUCCEED


ECHO ALL TESTS WERE SUCCEED
EXIT 0

:err
ECHO TEST FAILED
EXIT 1


REM Reverse(270) 
%PROGRAM% 270 
IF ERRORLEVEL 0 GOTO err 
ECHO Test "Reverse(270)" SUCCEED 

REM Reverse(-1) 
%PROGRAM% -1 
IF ERRORLEVEL 0 GOTO err 
ECHO Test "Reverse(-1)" SUCCEED 

REM Reverse("f") 
%PROGRAM% "f" 
IF ERRORLEVEL 0 GOTO err 
ECHO Test "Reverse("f")" SUCCEED 

REM Reverse("Hello World") 
%PROGRAM% "Hello World" 
IF ERRORLEVEL 0 GOTO err 
ECHO Test "Hello World" SUCCEED 

ECHO ALL TESTS WERE SUCCEED 
EXIT 0