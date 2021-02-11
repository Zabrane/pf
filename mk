#!/bin/sh

W=-Wno-int-conversion 

tcc -pedantic -funsigned-char -opf p.c -Os && ./pf
#gcc $W -opf p.c -Os  && ./pf
#clang -opf $W -Wno-pointer-sign p.c -Os  && ./pf

#/:~

