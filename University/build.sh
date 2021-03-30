#!/bin/bash 

if [ ! -d "build" ]; then 
mkdir build 
fi 

cd build 
cmake .. -G "MinGW Makefiles" 
mingw32-make 
./Project 
cd ..