## pf(f,a..)

`pf()` is a tiny `printf()` shim for embedded systems.

generally speaking, there is no portable way to implement a drop-in nostdlib
replacement for `printf(3)`, since `va_arg` is an architecture-specific
builtin, hence the mandatory:

**no userland code should ever mess with underlying ABI, and there are
no excuses for re-reimplementing any part of standard library, because
stdlibs are written by people who really know what they are doing.**

in the unlikely case you want `printf` in a setting where you
absolutely must ditch stdlib, `pf` is a simple reality hack that provides
a bare minimum `printf()` at a price of:

* one syscall `write(2)`
* one warning `int-conversion`
* total loss of floats and thread safety.

what you get:

* format string parser recognizes `%[%-][09][.09*]dcups`
* unsupported features are filtered from output
* `%d` and `%u` are also long longs
* freestanding binary ~9kb.

just like its real counterpart, `pf()` is extremely brittle, i.e. any mismatch
between the format string and positional arguments is probably a segfault.

since `tcc` is the best ISO C compiler available, you must define
the maximum number of arguments at compile time, see `VMX`. for `clang` and `gcc`,
the number of arguments is unbounded, same as for `printf(3)`.

## test

the code is tested with  `clang12`, `gcc10`, `tcc-mob`, both 32- and 64-bit. `makefile` targets are:

* `tcl` fat builds to default arch
* `[tcl]32` fat to 32-bit
* `[tcl]64` freestanding nostdlib 64-bit (linux-only, see `64.S`)
* `s64` dynamic library (not really useful for intended use cases)
* `r` reference output (uses `printf` instead of `pf`)

```
$ make t|c|l|t32|t64|c32|c64|l32|l64|s64|r

  (%)=(%) (kparc)=(kparc) (kparc)=(kparc) ()=()

   umx = (18446744073709551615)
   jmn = (-9223372036854775807)
   jmx = ( 9223372036854775807)
   imn = (         -2147483647)
   imx = (          2147483647)
  uimx = (          4294967295)

  pmx32 = (         0xffffffff)
  pmx64 = ( 0xffffffffffffffff)

  0|atw     |     atw|  3|3  |  0xdeadbeef|0x04 |  k|k  |%|
  1|nsl     |     nsl|  3|3  |  0xdeadbeef|0x04 |  k|k  |%|
  2|attila  |  attila|  6|6  |  0xdeadbeef|0x04 |  k|k  |%|
  3|icsa    |    icsa|  4|4  |  0xdeadbeef|0x04 |  k|k  |%|
  4|alex    |    alex|  4|4  |  0xdeadbeef|0x04 |  k|k  |%|
  5|ktye    |    ktye|  4|4  |  0xdeadbeef|0x04 |  k|k  |%|
  6|kparc   |   kparc|  5|5  |  0xdeadbeef|0x04 |  k|k  |%|

 pf: s=(i uncover the soul-destroying abhorrence) p=(0xcafebabe) c=(K) eot=(0x04) n=(53) //:~
```

## faq

> what's the idea?

`pf()` is a variadic macro which is used to initialize contents of
an anonymous uint64 array of length `VMX`, which is passed to `txpf()` on stack.
`txpf()` downcasts longs according to the format specification, and prints them.

> what's the catch?

stack overpressure, therefore:

a) if you are using `tcc`, choose `VMX` wisely

b) if you absolutely sure your pointers are 32-bit and you don't need to print
longs, redeclare `union` to use `UI` instead of `UJ`. if you're not sure what
any of this means, `pf()` is not for you. caveat emptor.

c) protect your stack.

> will it work on my operating system?

yes, but if you're lucky to have an operating system, you should use `printf(3)`.

> why the dummy `union{UJ}`?

to trick `gcc` into thinking that ptr-to-ULL coercion is not an error (`tcc` and `clang` are aware of that).

> why `int-conversion` warning?

ptr-to-ULL warning can be safely ignored. no lossy casts are taking place.

> why this software is written this way?

because this way the software is faster to write, easier to read, and safer to run.
your mileage may vary. the code is subject to terms of bsd-2-clause, except `_.h` which
is placed in public domain by the [regents of kparc](https://github.com/kparc).


`//:~`
