#!/bin/bash

CC="gcc"
FLAGS="-Wall -Wextra"
SRC="src"
OUT="machine"

$CC $FLAGS $SRC/*.c -o $OUT
