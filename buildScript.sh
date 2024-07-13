#!/bin/bash

# checks if cmake is installed
if command -v cmake &> /dev/null
then
    echo "cmake is installed, proceeding with build."

    # creates build dir
    mkdir -p build
    cd build

    # runs cmake and make
    cmake ..
    make
else 
    echo "cmake is not installed. Please install cmake and try again."
fi