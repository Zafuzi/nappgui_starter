#!/bin/bash

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo "\nRunning on: " ${machine}

flags = "Unix Makefiles" # linux

if machine == "Mac"; then
    flags = "XCode";
elif machine == "Cygwin"; then
    flags = "Visual Studio 17 2022"
elif machine == "MinGw"; then
    flags = "Visual Studio 17 2022"
fi

mkdir -p build;
cd build;
if cmake -G "Unix Makefiles" ../src; then
    cd hello;
    if make; then
        ./Debug/Hello
    fi
fi