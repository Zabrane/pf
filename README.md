## pf(f, a..)

`pf()` is a tiny `printf()` shim for embedded systems.

generally speaking, there is no portable way to implement a drop-in nostdlib
replacement for `printf(3)`, since `va_arg` is an architecture-specific
builtin, hence the mandatory:

**no userland code should ever mess with underlying ABI, and there are
no excuses for re-reimplementing any part of standard library, because
stdlibs are written by people who really know what they are doing.**

however, in the unlikely case you want `printf` in a setting where you 
absolutely must ditch stdlib, `pf` is a simple reality hack that provides
a bare minimum `printf()` at a price of:

* one syscall `write(2)`
* one warning `int-conversion`
* total loss of floats and thread safety.

what you get:

* format string parser recognizes `%[%-][09][.09*]dcups`
* unsupported features are filtered from output
* `%d` and `%u` are also long longs
* max number of arguments `VMX` is defined at compile time
* `clang12`, `gcc10`, `tcc-mob`, both 32/64-bit, see `makefile`
* freestanding binary ~9kb.

just like its real counterpart, `pf()` is extremely brittle, i.e. any mismatch
between the format string and positional arguments is probably a segfault.

## faq

> what's the idea?

`pf()` is a variadic macro which is used to initialize contents of 
an anonymous uint64 array of length `VMX`, which is passed to `txpf()` on stack.
`txpf()` downcasts longs according to the format specification, and prints them.

> what's the catch?

stack overpressure, therefore: a) choose `VMX` wisely b) if you absolutely sure 
your pointers are 32-bit and you don't need to print longs, redeclare the `union` 
to use `UI` instead of `UJ`. if you're not sure what any of this means, `pf()` 
is not for you. caveat emptor.

> why the dummy `union{UJ}`?

to trick `gcc` into thinking that ptr-to-ULL coercion is not an error (`tcc` and `clang` are aware of that).

> why `int-conversion` warning?

ptr-to-ULL warning can be safely ignored. no type-narrowing casts are taking place.


```
$ make t|c|l|t32|t64|c32|c64|l32|l64|s64

  (%)=(%) (kparc)=(kparc) (kparc)=(kparc) ()=()

  umx = (18446744073709551615)
  jmx = ( 9223372036854775807)
  imn = (         -2147483647)
  imx = (          2147483647)

  0|atw     |     atw|  3|3  |  0xdeadbeef|0x04 |  k|k  |%|
  1|nsl     |     nsl|  3|3  |  0xdeadbeef|0x04 |  k|k  |%|
  2|attila  |  attila|  6|6  |  0xdeadbeef|0x04 |  k|k  |%|
  3|icsa    |    icsa|  4|4  |  0xdeadbeef|0x04 |  k|k  |%|
  4|alex    |    alex|  4|4  |  0xdeadbeef|0x04 |  k|k  |%|
  5|ktye    |    ktye|  4|4  |  0xdeadbeef|0x04 |  k|k  |%|
  6|kparc   |   kparc|  5|5  |  0xdeadbeef|0x04 |  k|k  |%|

 pf: s=(i uncover the soul-destroying abhorrence) p=(0xcafebabe) c=(K) eot=(0x04) n=(53) //:~
```

`//:~`
