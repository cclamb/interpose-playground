#!/bin/sh

export DYLD_INSERT_LIBRARIES=./libInterposeMalloc.dylib
./main
