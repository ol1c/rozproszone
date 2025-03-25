#!/bin/bash
set -e

gcc -c minmax.c -o minmax.o
ar r lib_minmax.a minmax.o
gcc -c minmax_test.c -o minmax_test.o 2>/dev/null
gcc minmax_test.o lib_minmax.a -o minmax_wynik.out

gcc -c -Wall -fPIC -D_GNU_SOURCE fib.c
gcc fib.o -shared -o lib_fib.so
gcc -c fib_test.c -o fib_test.o 2>/dev/null
gcc fib_test.o -L. -l_fib -o fib_wynik.out
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:."

echo "Prezentacja aplikacji minmax z wykorzystaniem biblioteki statycznej:"
./minmax_wynik.out

echo
echo "Prezentacja aplikacji fibonacci z wykorzystaniem biblioteki dynamicznej:"
./fib_wynik.out