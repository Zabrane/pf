#!/bin/sh

W=-Wno-int-conversion

# dynlib
#clang -Wno-pointer-sign $W -shared -fPIC -nostdlib -rdynamic p.c -Os -o libpf.so

# nolibc
#tcc -DNOLIBC=1 -nostdlib -funsigned-char -opf p.c s.S -Os && ./pf

#tcc -w -funsigned-char -opf p.c -Os && ./pf
gcc $W -opf p.c -Os && ./pf
#clang -opf $W -Wno-pointer-sign p.c -Os  && ./pf

#/:~
