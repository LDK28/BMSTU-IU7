@ECHO OFF
FOR /L %%B IN (1,1,9) DO (call pos_test.cmd 0%%B)
FOR /L %%B IN (1,1,13) DO (call neg_test.cmd 0%%B)
DEL out.txt
