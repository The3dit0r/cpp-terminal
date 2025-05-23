@echo off
echo ====================================================
echo COMPILING
g++ main.cpp -o main.exe ./lib/printer/printer.cpp ./lib/global/global.cpp
echo COMPILE COMPLETE 
echo ====================================================
cls

echo RUNNING main.exe
main.exe
echo ====================================================


@echo on