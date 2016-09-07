


mingw32-make 

@echo off

Cd bin/verification

for  %%i in (*.exe) do start /wait "" "%%i"


Cd octave


octave-cli verification.m
