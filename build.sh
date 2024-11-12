#!/bin/bash

CC="gcc"
FLAGS="-Wall -Wextra"
SRC="src"
OUT="machine"

if [[ "$1" == "--debug" ]]; then
    FLAGS="$FLAGS -DDEBUG"
fi

$CC $FLAGS $SRC/*.c -o $OUT
