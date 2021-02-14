W=-fno-common -fno-asynchronous-unwind-tables -fstack-protector -Wno-int-conversion -Wno-int-to-pointer-cast

O=pf
F=-DPF

t:
	@tcc $F -w -o$O *.c -Os && ./$O
t32:
	@tcc $F -m32 -w -o$O *.c -Os && ./$O
t64:
	@tcc $F -m64 -DNOLC -nostdlib -w -o$O *.c 64.S -Os && ./$O

g:
	@gcc $F $W -o$O *.c -Os && ./$O
g32:
	@gcc $F -m32 $W -o$O *.c -Os && ./$O
g64:
	@gcc $F -m64 -DNOLC $W -nostdlib -ffreestanding -o$O *.c 64.S -Os && ./$O

l:
	@clang $F -o$O $W *.c -Os && ./$O
l32:
	@clang $F -m32 -o$O $W *.c -Os && ./$O
l64:
	@clang $F -m64 -DNOLC -nostdlib -ffreestanding -o$O $W *.c 64.S -Os && ./$O

s64:
	@clang $F -DLIB -Wno-pointer-sign $W -shared -fPIC -nostdlib -rdynamic *.c -Os -o lib$O.so

r:
	@clang -w -o$O *.c -Os && ./$O -UPF

#/:~
