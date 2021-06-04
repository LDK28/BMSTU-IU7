@ECHO OFF
FOR /L %%B IN (1,1,3) DO (call pos_test.cmd 0%%B)
FOR /L %%B IN (1,1,3) DO (call neg_test.cmd 0%%B)
DEL out.txt
