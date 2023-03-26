@echo off

set PROGRAM="%~1"

%PROGRAM% input.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\output.txt output1.txt || goto err

echo Successful program test
exit 0

:err
echo Failed program test
exit 1