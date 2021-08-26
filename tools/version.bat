@echo off

for /f %%i in ('git rev-list --count head') do set version=%%i

echo #define VERSION %version%> ..\\src\\shared\\utils\\version.hpp

echo Version is %version%.
