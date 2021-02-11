W=-Wno-int-conversion
O=pf

#tcc -w -funsigned-char -opf p.c -Os && ./pf

# nostdlib (linux/x86)
t:
	#clang -m32 -o$O $W -Wno-pointer-sign *.c  -O0 && ./$O
	tcc -m32 -funsigned-char -o$O *.c -Os && ./$O
t32:
	tcc -m32 -nostdlib -funsigned-char -o$O *.c 32.S -Os && ./$O
t64:
	tcc -m64 -nostdlib -funsigned-char -o$O *.c 64.S -Os && ./$O
g64:
	gcc -nostdlib -ffreestanding -o$O *.c 64.S -Os && ./$O
l64:
	clang -o$O $W -ffreestanding -nostdlib -Wno-pointer-sign *.c 64.S -O0 && ./$O
s64:
	clang -Wno-pointer-sign $W -shared -fPIC -nostdlib -rdynamic *.c -Os -o lib$O.so
#/:~
