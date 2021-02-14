W=-fno-common -fno-asynchronous-unwind-tables -fno-stack-protector

O=pf
S=pf.c
A=`uname -ms`
F=-DPF -DPFA="\"$A\""
L=/opt/clang/bin/clang

m: c
	@echo
	gcc -Os -DNOLC -DPF -Werror -pedantic -om m.c
	@echo
	@strip m
	@ls -la m
	@./m

t:
	@tcc $F -w -o$O $S -O0 -g && ./$O
t32:
	@tcc $F -m32 -w -o$O $S -Os && ./$O
t64:
	@tcc $F -m64 -DNOLC -nostdlib -w -o$O $S s.S -Os && ./$O

g:
	@gcc $F $W -o$O $S -O0 -g && ./$O
g32:
	@gcc $F -m32 $W -o$O $S -Os && ./$O
g64:
	@gcc $F -m64 -DNOLC $W -nostdlib -ffreestanding -o$O $S s.S && ./$O

l:
	@$L $F -o$O $W $S -O0 -g && ./$O
l32:
	@$L $F -m32 -o$O $W $S -Os && ./$O
l64:
	@$L $F -m64 -DNOLC -nostdlib -ffreestanding -o$O $W $S s.S -Os && ./$O

s64:
	@$L $F -DLIB -Wno-pointer-sign $W -shared -fPIC -nostdlib -rdynamic $S -Os -o lib$O.so

r:
	@$L -w -o$O $S -Os -DNOPF -DPFA="\"$A\"" && ./$O

arm64:
	@$L $F -m64 -DNOLC -nostdlib -ffreestanding -o$O $W $S -Os && ./$O

c:
	@rm -f m pf

.PHONY: c all

#/:~
