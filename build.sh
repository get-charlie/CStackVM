#!/bin/bash

CC="gcc"
FLAGS="-Wall -Wextra"
SRC="src"
OUT="machine"

if [[ "$1" == "debug" ]]; then
    echo "Compiling in debug mode."
    FLAGS="$FLAGS -DDEBUG"
fi

$CC $FLAGS $SRC/*.c -o $OUT
