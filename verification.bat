


mingw32-make 

@echo off

Cd bin/verification



for  %%i in (*.exe) do  "%%i"

Cd octave


octave-cli verification.m
