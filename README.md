# Misc
Short programs unsuitable for their own repositories.  
This list is more or less in the order of commits  
Additions, new programs, and fixes are welcome

## Licensing
**Please view the license header in each of the source code files**; files without license headers are part of the public domain.

### [collatz.c](collatz.c)
Collatz conjecture for a set range of numbers

### [autodhcp.sh](autodhcp.sh)
Menu-driven interface for starting dhcpcd on target interface

### [true.s](true.s) & [false.s](false.s)
POSIX true and false in x86 NASM/Intel syntax, written (in humor) for Linux from inspirarion after viewing GNU coreutils' source

### [bit.c](bit.c)
A small example of bitpacking in C.

### [taocp\_1.2.1\_P.c](taocp\_1.2.1\_P.c) & [taocp\_1.2.1\_P\_verify.sh](taocp\_1.2.1\_P\_verify.sh)
`.c`: Equation (1) in Donald Knuth's *"The Art of Computer Programming"*, Volume 1, Section 1.2.1  
`_verify.sh`: Used to verify the output of the aforementioned program

### [fizzbuzz.c](fizzbuzz.c)
An implementation of [FizzBuzz](http://c2.com/cgi/wiki?FizzBuzzTest) in C.

### [fisher-yates.c](fisher-yates.c)
Simple implementation of [Fisher-Yates' algorithm](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm).

### [isPrime.c](isPrime.c)
An efficient algorithm for checking if a number is prime using bit fiddling and halving the number of divisor halving with 
division by odd numbers only.

### [today.c](today.c)
Display the day of the week and the date using `time()`, `strftime()`, and [Zeller's congruence](https://en.wikipedia.org/wiki/Zeller%27s_congruence).

### [smallhello.s](smallhello.s)
Tiny hello world, totalling 125 bytes after being assembled, created by smashing ELF headers together and embedding code in the empty `e_ident` space, 
and `e_shoff`, `e_flags` space, which is only possible by using 64-bit executables, since it uses larger fields than 32-bit ELF. Theoretically, it could be made smaller by
using a couple more assembly tricks. As of the first addition to this repository, it has a partially correct ELF header, though `objdump` doesn't play nice with it, `file` reads most of the header correctly.

### [tictactoe/](tictactoe)
A simple Tic Tac Toe game written in C (now with headers for including in other programs).

### [rot/](rot)
A Caesar cipher implementation with arbitrary radix selection.

### [kexec.sh](kexec.sh)
A simple front-end to kexec.
