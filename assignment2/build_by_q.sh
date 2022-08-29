#!/bin/bash
# This script builds the C code of a given question, and runs it
# Example usage:
# ./build_by_q.sh 1 # will build ex2_q1.c and run it
#
set -o nounset -e
QNO=$1
cd $(dirname $0)
gcc ex2_q${QNO}.c -o autobuilt_out.o

# Run executable
./autobuilt_out.o
rm -f autobuilt_out.o
