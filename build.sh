#!/bin/bash

gcc -Wall -fPIC -shared -o /app/libcsv.so libcsv.c
gcc -Wall -o /app/test_libcsv test_libcsv.c -L/app -lcsv
gcc -o test_libcsv test_libcsv.c -I/usr/include/python3.8 -lpython3.8