W=-fno-common -fno-asynchronous-unwind-tables -fno-stack-protector -Wno-int-conversion -Wno-int-to-pointer-cast
O=pf

t32:
	@tcc -m32 -w -o$O *.c -Os && ./$O
t64:
	@tcc -m64 -DNOLC=1 -nostdlib -w  -o$O *.c 64.S -Os && ./$O

g32:
	@gcc -m32 $W -o$O *.c -Os && ./$O
g64:
	@gcc -m64 $W -nostdlib -ffreestanding -o$O *.c 64.S -Os && ./$O

l32:
	@clang -m32 -o$O $W -Wno-pointer-sign *.c -Os && ./$O
l64:
	@clang -DNOLC=1 -ffreestanding -o$O $W  -Wno-pointer-sign *.c  -Os && ./$O

s64:
	@clang -DLIB -Wno-pointer-sign $W -shared -fPIC -nostdlib -rdynamic *.c -Os -o lib$O.so

#/:~
