#!/bin/bash

set -e

CFLAGS="-Wall"
CFLAGS+=" -DUSE_GETLINE"
OPTCFLAGS="${CFLAGS} -O2"
DBGCFLAGS="${CFLAGS} -ggdb3 -DDEBUG"

rm -f *.exe *.dbg

gcc ${OPTCFLAGS}         ${ACTION} dupe_pkg_unit_test.c hex2bin.c -o dupe_pkg_unit_test.exe
gcc ${DBGCFLAGS}         ${ACTION} dupe_pkg_unit_test.c hex2bin.c -o dupe_pkg_unit_test.dbg
gcc ${OPTCFLAGS} -static ${ACTION} dupe_pkg_unit_test.c hex2bin.c -o dupe_pkg_unit_test.static.exe

gcc ${OPTCFLAGS}         ${ACTION} main.c hex2bin.c xform.c output.c -o xform.exe
gcc ${DBGCFLAGS}         ${ACTION} main.c hex2bin.c xform.c output.c -o xform.dbg
gcc ${OPTCFLAGS} -static ${ACTION} main.c hex2bin.c xform.c output.c -o xform.static.exe

strip *.exe
