#!/bin/sh

W=-Wno-int-conversion

# nolibc
#tcc -pedantic -DNOLIBC=1 -nostdlib -funsigned-char -opf p.c s.S -Os && ./pf

#tcc -pedantic -funsigned-char -opf p.c -Os && ./pf
#gcc $W -opf p.c -Os  && ./pf
clang -opf $W -Wno-pointer-sign p.c -Os  && ./pf

#/:~
