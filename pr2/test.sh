#!/bin/bash

# Remove or move existing test.txt if you'd rather overwrite it each time
rm -f test.txt

# Execute each cmc command, redirecting and appending output to test.txt
./cmc -v -t tmp/b00.c >> test.txt 2>&1
./cmc -v -t tmp/b01.c >> test.txt 2>&1
./cmc -v -t tmp/b02.c >> test.txt 2>&1
./cmc -v -t tmp/b03.c >> test.txt 2>&1
./cmc -v -t tmp/b04.c >> test.txt 2>&1
./cmc -v -t tmp/b05.c >> test.txt 2>&1