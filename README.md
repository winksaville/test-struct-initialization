# Test structure initialization

Test structure initialization as [initialization is bonkers](https://blog.tartanllama.xyz/c++/2017/01/20/initialization-is-bonkers/),
and the bottom line is *initialize your variables*!

If you add a user defined constructor to a then you "must" initialize it properly. Here
I've changed start, length to a std::string and then used ZeroMemory(\*this) to initialize.
This seems to work, but not as flexible as using
[aggregrate initialization](http://en.cppreference.com/w/cpp/language/aggregate_initialization)
with constructors created by the compiler.

# Prerequistes
- clang
- make

# Build
```
$ make
clang -O0 -g --std=c++14 -Weverything -Werror -Wno-padded -Wno-format-pedantic -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c99-extensions  -DDBG=0   -x c++ -c si.cc -o si.o
objdump -S -M x86_64,intel si.o > si.asm
clang -O0 -g --std=c++14 -Weverything -Werror -Wno-padded -Wno-format-pedantic -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c99-extensions  -DDBG=0   -x c++ -c Structure.cc -o Structure.o
objdump -S -M x86_64,intel Structure.o > Structure.asm
clang -lstdc++ -lm si.o Structure.o -o si
objdump -S -M x86_64,intel si > si.asm
```

# Run `./si` directly as below or `make run` does the same thing
```
$ ./si
sizeof(Structrue)=0x38
s=Hi wink
s=bye
s=0x7fff049f5e28
s=0x7fff049f5e28:Empty
length=0x0
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
table.limits->has_max=0x0
s=0x7fff049f5df0
s=0x7fff049f5df0:Empty
length=0x0
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
table.limits->has_max=0x0
s=0x164d030
s=0x164d030:Empty
length=0x0
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
table.limits->has_max=0x0
```

# Run using valgrind
```
$ make vg
valgrind --leak-check=yes --track-origins=yes ./si
==1767== Memcheck, a memory error detector
==1767== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1767== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==1767== Command: ./si
==1767== 
sizeof(Structrue)=0x38
s=Hi wink
s=bye
s=0x1ffefffeb8
s=0x1ffefffeb8:Empty
length=0x0
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
table.limits->has_max=0x0
s=0x1ffefffe80
s=0x1ffefffe80:Empty
length=0x0
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
table.limits->has_max=0x0
s=0x5aa00c0
s=0x5aa00c0:Empty
length=0x0
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
table.limits->has_max=0x0
==1767== 
==1767== HEAP SUMMARY:
==1767==     in use at exit: 0 bytes in 0 blocks
==1767==   total heap usage: 3 allocs, 3 frees, 73,784 bytes allocated
==1767== 
==1767== All heap blocks were freed -- no leaks are possible
==1767== 
==1767== For counts of detected and suppressed errors, rerun with: -v
==1767== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
