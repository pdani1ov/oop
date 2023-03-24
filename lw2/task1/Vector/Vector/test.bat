@echo off

set PROGRAM="%~1"

%PROGRAM% < testEmpty.txt > "%TEMP%\output.txt"
fc %TEMP%\output.txt outputTestEmpty.txt || goto err

%PROGRAM% < testIncorrectChars.txt > "%TEMP%\output.txt"
fc %TEMP%\output.txt outputIncorrectChars.txt || goto err

%PROGRAM% < testCorrectInput.txt > "%TEMP%\output.txt"
fc %TEMP%\output.txt outputCorrectInput.txt || goto err

echo Successful program test
exit 0

:err
echo Failed program test
exit 1