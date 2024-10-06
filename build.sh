#!/bin/bash

function _display()
{
    echo -e "[\033[1;32m$1\033[0m] $2"
}

_display "START" "Welcome to $0 auto-build script"

if [ -f "lumen" ]; then
    _display "CLEAN" "Removing old executable..."
    rm lumen > /dev/null 2>&1
fi
if [ -f "Makefile" ]; then
    _display "CLEAN" "Removing old Makefile..."
    rm Makefile > /dev/null 2>&1
fi

_display "BUILD" "Building Lumen..."

time (bash scripts/automakefile.sh lumen && _display "COMPILE" "Compiling Makefile..." && make)
