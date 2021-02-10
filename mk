#!/bin/sh

W=-Wno-int-conversion 

#tcc -pedantic -funsigned-char -opf p.c -Os
#gcc $W -opf p.c -Os
clang -opf $W -Wno-pointer-sign p.c -Os

./pf

#/:~

