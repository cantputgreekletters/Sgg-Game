@echo off
g++ main.cpp ./sgg/*.cpp ./include/*.cpp ./dependencies/*.dll -DGLM_ENABLE_EXPERIMENTAL -I. -I./freetype2 -o main

if errorlevel 1 (
    echo Compilation failed!
    pause
    exit /b 1
) else (
    echo Compilation successful!
    pause
)