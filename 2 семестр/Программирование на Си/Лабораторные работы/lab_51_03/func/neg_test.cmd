@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe c neg_%~1_in.txt
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
..\app.exe s out.bin
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
..\app.exe p out.bin > out.txt
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
FC /N neg_%~1_out.txt out.txt
DEL out.bin
:END

..\app.exe c qwerty.txt
IF %ERRORLEVEL% EQU 0 ECHO EXTRA NEG TEST 1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
..\app.exe s qwerty.txt
IF %ERRORLEVEL% EQU 0 ECHO EXTRA NEG TEST 2 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
..\app.exe p qwerty.txt
IF %ERRORLEVEL% EQU 0 ECHO EXTRA NEG TEST 3 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END

..\app.exe c qwerty.txt qwe.txt
IF %ERRORLEVEL% EQU 0 ECHO EXTRA NEG TEST 4 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END

..\app.exe t pos_01_in.txt
IF %ERRORLEVEL% EQU 0 ECHO EXTRA NEG TEST 1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END

