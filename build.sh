#!/bin/bash
g++ -o online_banking_system.exe main.cpp
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi
echo "Compilation successful."
