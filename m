#!/bin/bash

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

echo -e "\n- - - - - - - - - - Running on: $machine - - - - - - - - - -\n"

flags=""

if [ "$machine" = "Linux" ]; then
    flags="Unix Makefiles"

elif [ "$machine" = "Mac" ]; then
    flags="XCode";

elif [ "$machine" = "Cygwin" ]; then
    flags="Visual Studio 17 2022"

elif [ "$machine" = "MinGw" ]; then
    flags="Visual Studio 17 2022"

else
    echo -e "\nMachine architecture not supported\n"
    exit 0;
fi

mkdir -p build;
cd build;
if cmake -G "$flags" ../src; then
    cd hello;
    if make; then
        ./Debug/Hello
    fi
fi