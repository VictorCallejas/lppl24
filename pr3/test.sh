#!/bin/bash

# Remove or move existing test.txt if you'd rather overwrite it each time
rm -f test.txt

# Execute each cmc command, redirecting and appending output to test.txt
./cmc -v -t tmp/c00.c >> test.txt 2>&1
./cmc -v -t tmp/c01.c >> test.txt 2>&1
./cmc -v -t tmp/c02.c >> test.txt 2>&1
./cmc -v -t tmp/c03.c >> test.txt 2>&1
./cmc -v -t tmp/c04.c >> test.txt 2>&1
./cmc -v -t tmp/c05.c >> test.txt 2>&1
./cmc -v -t tmp/c06.c >> test.txt 2>&1
./cmc -v -t tmp/c07.c >> test.txt 2>&1