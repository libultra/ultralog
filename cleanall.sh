#!/bin/sh

if [ -f Makefile ]; then
    make distclean
fi

rm -rf Makefile.in aclocal.m4 autom4te.cache config.guess config.sub configure depcomp install-sh ltmain.sh m4 missing src/Makefile.in src/include/ultralog/config.h.in src/include/ultralog/config.h.in~ test/Makefile.in doc/Makefile.in ar-lib compile doc/doxygen_sqlite3.db
