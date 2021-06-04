@ECHO OFF
SET /p args=<pos_%~1_args.txt
IF "%1"=="" ECHO ---NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe %args% > out.txt
IF %ERRORLEVEL% NEQ 0 ECHO ---POS TEST %~1 ::FAIL:: RETURN CODE IS NOT ZERO... & GOTO :END
FC /N pos_%~1_out.txt out.txt
:END
