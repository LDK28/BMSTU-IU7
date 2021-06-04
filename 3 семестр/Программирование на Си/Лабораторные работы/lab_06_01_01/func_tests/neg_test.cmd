@ECHO OFF
SET /p args=<neg_%~1_args.txt
IF "%1"=="" ECHO ---NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe %args% > out.txt
IF %ERRORLEVEL% NEQ 1 ECHO ---NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
FC /N neg_%~1_out.txt out.txt
:END