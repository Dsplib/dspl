


mingw32-make 

@echo off

Cd bin/verification

for  %%i in (*.exe) do start /wait "" "%%i"


Cd octave


for  %%i in (*.m) do octave-cli "%%i"