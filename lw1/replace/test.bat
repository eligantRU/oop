@ECHO OFF

set PROGRAM="%~1"

REM invalid arguments
CALL %PROGRAM% 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
C:\Windows\System32\FC %TEMP%\err.txt correctTest\correctInvalidArguments.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for invalid arguments SUCCEED

REM replace string is empty
CALL %PROGRAM% "inputTest\multiline-file.txt" %TEMP%\emptyReplaceString.txt "pony" ""
IF ERRORLEVEL 1 GOTO errs
C:\Windows\System32\FC %TEMP%\emptyReplaceString.txt correctTest\correctEmptyReplaceString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\emptyReplaceString.txt
ECHO Test for empty replace string SUCCEED

REM search string is empty
CALL %PROGRAM% "inputTest\multiline-file.txt" %TEMP%\emptySearchString.txt "" "testing" 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
C:\Windows\System32\FC %TEMP%\err.txt correctTest\correctEmptySearchString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\emptySearchString.txt
DEL %TEMP%\err.txt
ECHO Test for empty search string SUCCEED

REM replace "pony" to "elephant"
CALL %PROGRAM% "inputTest\multiline-file.txt" %TEMP%\elephantReplaceString.txt "pony" "elephant"
IF ERRORLEVEL 1 GOTO errs
C:\Windows\System32\FC %TEMP%\elephantReplaceString.txt correctTest\correctElephantReplaceString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\elephantReplaceString.txt
ECHO Test for replace "pony" to "elephant" SUCCEED

REM replace "pony" to "pony pony pony"
CALL %PROGRAM% "inputTest\multiline-file.txt" %TEMP%\PonyPonyPonyReplaceString.txt "pony" "pony pony pony"
IF ERRORLEVEL 1 GOTO errs
C:\Windows\System32\FC %TEMP%\PonyPonyPonyReplaceString.txt correctTest\correctPonyPonyPonyReplaceString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\PonyPonyPonyReplaceString.txt
ECHO Test for replace "pony" to "pony pony pony" SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
