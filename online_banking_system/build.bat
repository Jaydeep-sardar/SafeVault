@echo off
g++ -o online_banking_system.exe main.cpp
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)
echo Compilation successful.
