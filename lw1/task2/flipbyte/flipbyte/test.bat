@echo off

set PROGRAM="%~1"

%PROGRAM% "6" > "%TEMP%\output.txt"
fc %TEMP%\output.txt output1.txt || goto err

%PROGRAM% "256" > "%TEMP%\output.txt"
fc %TEMP%\output.txt output2.txt || goto err

%PROGRAM% "-1" > "%TEMP%\output.txt"
fc %TEMP%\output.txt output2.txt || goto err

%PROGRAM% "hello" > "%TEMP%\output.txt"
fc %TEMP%\output.txt output3.txt || goto err

echo Successful program test
exit 0

:err
echo Failed program test
exit 1