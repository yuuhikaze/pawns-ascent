#!/bin/bash

set -uo pipefail
IFS=$'\n'

mkdir build
cmake -DCMAKE_PREFIX_PATH=/home/user/Tools/software/Slint-cpp-1.8.0-Linux-x86_64 -B build
cmake --build build
