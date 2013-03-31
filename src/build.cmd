@echo off

@if exist prg1.exe del prg1.exe

rem ############################
rem # compile project with ggc #
rem ############################

cd obj
gcc S:\src\config.c    -c
gcc S:\src\strext.c    -c
gcc S:\src\stmachine.c -c
gcc S:\src\prg1.c      -c
gcc S:\src\sysdata.c   -c
gcc S:\src\util.c      -c
cd ..

gcc S:\obj\config.o S:\obj\util.o S:\obj\sysdata.o S:\obj\stmachine.o S:\obj\strext.o S:\obj\prg1.o -o prg1

rem #############################

@echo on
