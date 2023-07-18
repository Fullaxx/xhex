#!/bin/bash

set -e

# Unit Tests for bit reversal
echo "FEDCBA9876543210FEDCBA9876543210" | XOP01=reverse ./xform.exe | grep -q "7F3B5D196E2A4C087F3B5D196E2A4C08"
echo "0293A4B5C6D7E8F9" | XOP01=reverse ./xform.exe | grep -q "40C925AD63EB179F"

# Unit Tests for bit inversion
echo "0123456789ABCDEF" | XOP01=invert ./xform.exe | grep -q "FEDCBA9876543210"

# Unit Tests for skip and cut
echo "AAABACAD" | XOP01=cut=1 ./xform.exe | grep -q "AA"
echo "AAABACAD" | XOP01=skip=1 ./xform.exe | grep -q "ABACAD"

# Unit Tests for multiple operations
echo "0123456789ABCDEF" | XOP01=skip=1 XOP02=invert ./xform.exe | grep -q "DCBA9876543210"
echo "0293A4B5C6D7E8F9" | XOP01=reverse XOP02=invert ./xform.exe | grep -q "BF36DA529C14E860"
