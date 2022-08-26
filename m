#!/bin/bash

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=MacOS;;
    CYGWIN*)    machine=Windows;;
    MINGW*)     machine=Windows;;
    MSYS_NT*)   machine=Windows;;
    *)          machine="UNKNOWN:${unameOut}"
esac

echo -e "\n- - - - - - - - - - Running on: $machine - - - - - - - - - -\n"

flags=""

if [ "$machine" = "Linux" ]; then
    flags="Unix Makefiles"

elif [ "$machine" = "MacOS" ]; then
    flags="Xcode";

elif [ "$machine" = "Windows" ]; then
    echo -e "\nPlease use m.bat\n"
    exit 0;

else
    echo -e "\nMachine architecture not supported\n"
    exit 0;
fi

rm -rf ./build;
mkdir -p build;
cd build;
if cmake -G "$flags" ../src; then
    if [ "$machine" = "Linux" ]; then
        cd hello;
        if make; then
            ./Debug/Hello
        fi
    fi

    if [ "$machine" = "MacOS" ]; then
        open NAppGUI.xcodeproj/
    fi
fi