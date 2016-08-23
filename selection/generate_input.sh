#!/bin/bash

# Install coreutils and use gshuf in you're on a Mac

shuf -i 1-1000000 -n 1000000 > A.txt
shuf -i 1-1000000 -n 100 > B.txt
