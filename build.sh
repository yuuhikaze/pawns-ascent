#!/bin/bash

set -uo pipefail
IFS=$'\n'

init() {
    mkdir -p build/packages
}

build() {
    cmake -DCMAKE_PREFIX_PATH=/home/user/Tools/software/Slint-cpp-1.8.0-Linux-x86_64 -B build
    cmake --build build
}

package() {
    build
    cpack --config build/CPackConfig.cmake
}

documentation() {
    cat <<'EOF'
OPTIONS
    -h: Displays documentation
    -b: Create build
    -p: Package app
EOF
}

while getopts ':hbp' flags; do
    case "$flags" in
    b)
        init
        build
        ;;
    p)
        init
        package
        ;;
    h) documentation ;;
    *)
        echo -e "Unrecognized option\nTry \`build.sh -h\` for more information"
        exit
        ;;
    esac
done

[ -z "$*" ] && echo -e "Unrecognized option\nTry \`build.sh -h\` for more information"
