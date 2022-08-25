#!/bin/bash

mkdir -p build;
cd build;
if cmake -G "Unix Makefiles" ../src; then
    cd hello;
    if make; then
        ./Debug/Hello
    fi
fi