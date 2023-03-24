@echo off

set PROGRAM="%~1"

%PROGRAM% < testDoubleDecode.txt > "%TEMP%\output.txt"
fc %TEMP%\output.txt outputDoubleDecode.txt || goto err

%PROGRAM% < testEmpty.txt > "%TEMP%\output.txt"
fc %TEMP%\output.txt outputEmpty.txt || goto err

%PROGRAM% < testCorrect.txt > "%TEMP%\output.txt"
fc %TEMP%\output.txt outputCorrect.txt || goto err

%PROGRAM% < test4.txt > "%TEMP%\output.txt"
fc %TEMP%\output.txt output4.txt || goto err

echo Successful program test
exit 0

:err
echo Failed program test
exit 1