@echo off

set PROGRAM="%~1"

%PROGRAM% input1.txt %TEMP%\output.txt 1231234 fff
fc %TEMP%\output.txt output1.txt || goto err

%PROGRAM% input2.txt %TEMP%\output.txt ma mama
fc %TEMP%\output.txt output2.txt || goto err

%PROGRAM% input3.txt %TEMP%\output.txt 1 2
fc %TEMP%\output.txt output3.txt || goto err

echo Successful program test
exit 0

:err
echo Failed program test
exit 1