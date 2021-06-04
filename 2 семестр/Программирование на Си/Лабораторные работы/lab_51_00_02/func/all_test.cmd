@ECHO OFF
FOR /L %%B IN (1,1,2) DO (call pos_test.cmd 0%%B)
FOR /L %%B IN (1,1,3) DO (call neg_test.cmd 0%%B)
..\app.exe neg_04_in.txt qwerty > out.txt
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST 04 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
FC /N neg_04_out.txt out.txt
DEL out.txt
