@echo off
echo Updating submodules...
git submodule update --init --remote --recursive
echo Generating project files...
call "tools/premake5.exe" vs2022 --file=premake.lua