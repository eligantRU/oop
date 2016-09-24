@ECHO OFF

set PROGRAM="%~1"

REM No params
CALL %PROGRAM% 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\err.txt
ECHO Test "no params" SUCCEED 

REM double minus
CALL %PROGRAM% inputTest\matrix3.txt 2> %TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctMatrix3.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for double minus SUCCEED

REM too much numbers in line
CALL %PROGRAM% inputTest\matrix9.txt 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctMatrix9.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for too much numbers in line SUCCEED

REM too much lines in file
CALL %PROGRAM% inputTest\matrix10.txt 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctMatrix10.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for too much lines in file SUCCEED

CALL %PROGRAM% inputTest\matrix1.txt > %TEMP%\matrix.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\matrix.txt correctTest\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\matrix.txt
ECHO Test for the 1st matrix SUCCEED

CALL %PROGRAM% inputTest\matrix2.txt > %TEMP%\matrix.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\matrix.txt correctTest\correctMatrix2.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\matrix.txt
ECHO Test for the 2nd matrix SUCCEED

CALL %PROGRAM% inputTest\matrix4.txt > %TEMP%\matrix.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\matrix.txt correctTest\correctMatrix4.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\matrix.txt
ECHO Test for the 4th matrix SUCCEED

CALL %PROGRAM% inputTest\matrix6.txt > %TEMP%\matrix.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\matrix.txt correctTest\correctMatrix6.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\matrix.txt
ECHO Test for the 6th matrix SUCCEED

CALL %PROGRAM% inputTest\matrix8.txt > %TEMP%\matrix.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\matrix.txt correctTest\correctMatrix8.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\matrix.txt
ECHO Test for the 8th matrix SUCCEED

REM det = 0
CALL %PROGRAM% inputTest\matrix5.txt > %TEMP%\matrix.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\matrix.txt correctTest\correctMatrix5.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\matrix.txt
ECHO Test for the 5th matrix(det = 0) SUCCEED

REM det = 0
CALL %PROGRAM% inputTest\matrix7.txt > %TEMP%\matrix.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\matrix.txt correctTest\correctMatrix7.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\matrix.txt
ECHO Test for the 7th matrix(det = 0) SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
