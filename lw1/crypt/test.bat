@ECHO OFF

set PROGRAM="%~1"

REM No params
CALL %PROGRAM% 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test "no params" SUCCEED 

REM Invalid <mode>
CALL %PROGRAM% bla inputTest\empty.txt %TEMP%\out.txt 0 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctInvalidMode.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
DEL %TEMP%\out.txt
ECHO Test "Invalid <mode>" SUCCEED 

REM <key> = -1
CALL %PROGRAM% crypt inputTest\empty.txt %TEMP%\out.txt -1 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctKey-1.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
DEL %TEMP%\out.txt
ECHO Test "<key> = -1" SUCCEED 

REM <key> = 270
CALL %PROGRAM% crypt inputTest\empty.txt %TEMP%\out.txt 270 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctKey270.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
DEL %TEMP%\out.txt
ECHO Test "<key> = 270" SUCCEED 

REM <key> = 'F'
CALL %PROGRAM% crypt inputTest\empty.txt %TEMP%\out.txt F 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctKeyF.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
DEL %TEMP%\out.txt
ECHO Test "<key> = 'F'" SUCCEED 

REM EmptyFile
CALL %PROGRAM% crypt inputTest\empty.txt %TEMP%\out.txt 255
IF ERRORLEVEL 1 GOTO errs 
FC %TEMP%\out.txt correctTest\correctEmpty.txt 
IF ERRORLEVEL 1 GOTO errs 
DEL %TEMP%\out.txt 
ECHO Test "EmptyFile" SUCCEED

REM OneLine File 104 crypt
CALL %PROGRAM% crypt inputTest\OneLine104.txt %TEMP%\out.txt 104
IF ERRORLEVEL 1 GOTO errs 
FC %TEMP%\out.txt correctTest\correctOneLine104Crypt.txt 
IF ERRORLEVEL 1 GOTO errs 
DEL %TEMP%\out.txt 
ECHO Test "OneLine File 104 crypt" SUCCEED

REM OneLine File 104 decrypt
CALL %PROGRAM% decrypt inputTest\OneLine104Decrypt.txt %TEMP%\out.txt 104
IF ERRORLEVEL 1 GOTO errs 
FC %TEMP%\out.txt correctTest\correctOneLine104Decrypt.txt 
IF ERRORLEVEL 1 GOTO errs 
DEL %TEMP%\out.txt 
ECHO Test "OneLine File 104 decrypt" SUCCEED

REM Multiline File 55 crypt
CALL %PROGRAM% crypt inputTest\Multiline55.txt %TEMP%\out.txt 55
IF ERRORLEVEL 1 GOTO errs 
FC %TEMP%\out.txt correctTest\correctMultiline55Crypt.txt 
IF ERRORLEVEL 1 GOTO errs 
DEL %TEMP%\out.txt 
ECHO Test "Multiline File 55 crypt" SUCCEED

REM Multiline File 55 decrypt
CALL %PROGRAM% decrypt inputTest\Multiline55Decrypt.txt %TEMP%\out.txt 55
IF ERRORLEVEL 1 GOTO errs 
FC %TEMP%\out.txt correctTest\correctMultiline55Decrypt.txt 
IF ERRORLEVEL 1 GOTO errs 
DEL %TEMP%\out.txt 
ECHO Test "Multiline File 55 decrypt" SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
