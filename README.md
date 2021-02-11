## pf(f, a..)

generally speaking, there exists no portable way to implement a nostdlib
shim for `printf(3)`, since `va_arg` is an architecture-specific
builtin.

the mandatory:

**no userland code should ever mess with underlying ABI, and there are
no excuses for re-reimplementing any part of standard library, because
stdlibs are written by people who really know what they are doing.**

however, in the unlikely case you want `printf` in a setting where you 
absolutely must ditch stdlib, `pf` is a simple reality hack that provides
a bare minimum `printf()` at a price of:

* one system call `write(2)`
* one warning `int-conversion`

* format string parser recognizes `%[%-][09][.09*]cdps`
* `d` supports long long, floats are not supprted
* max number of arguments `VMX` must be configured at compile time.

```
$ ./mk (tcc|gcc|clang)

  (%)=(%) (kparc)=(kparc) (kparc)=(kparc) ()=()

  jmx = 9223372036854775807
  imn =         -2147483647
  imx =          2147483647

  0|atw     |     atw|  3|3  |  0xdeadbeef|0x04 |  k|k  |%|
  1|nsl     |     nsl|  3|3  |  0xdeadbeef|0x04 |  k|k  |%|
  2|attila  |  attila|  6|6  |  0xdeadbeef|0x04 |  k|k  |%|
  3|icsa    |    icsa|  4|4  |  0xdeadbeef|0x04 |  k|k  |%|
  4|alex    |    alex|  4|4  |  0xdeadbeef|0x04 |  k|k  |%|
  5|kparc   |   kparc|  5|5  |  0xdeadbeef|0x04 |  k|k  |%|

 pf: s=(i uncover the soul-destroying abhorrence) p=(0xcafebabe) c=(K) eot=(0x04) n=(53) //:~
```

caveat emptor.


`//:~`
