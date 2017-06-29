# Test structure initialization

Test structure initialization as [initialization is bonkers](https://blog.tartanllama.xyz/c++/2017/01/20/initialization-is-bonkers/),
and the bottom line is *initialize your variables*!

As it turns out based on my experiments this rule is good and the programmer should have a
default constructor. But for `struct`'s where all fields are public, none of these
fields have default initializers and there are no virtual methods. Basically they are data
bags. Then it looks like the best approach is to let the compiler create the default
constructor and destructors. This will allow the use of
[aggregrate initialization](http://en.cppreference.com/w/cpp/language/aggregate_initialization).

# Prerequistes
- clang
- make

# Build
```
$ make
$ make
clang -O0 -g --std=c++14 -Weverything -Wno-padded -Wno-format-pedantic -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c99-extensions  -DDBG=0   -x c++ -c si.cc -o si.o
objdump -S -M x86_64,intel si.o > si.asm
clang -O0 -g --std=c++14 -Weverything -Wno-padded -Wno-format-pedantic -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c99-extensions  -DDBG=0   -x c++ -c Structure.cc -o Structure.o
objdump -S -M x86_64,intel Structure.o > Structure.asm
clang -lstdc++ -lm si.o Structure.o -o si
objdump -S -M x86_64,intel si > si.asm
```

# Run `./si` directly as below or `make run` does the same thing
```
$ ./si
sizeof(Structrue)=0x28
s=0x601ru050
start=(nil):(null)
length=0x0
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
....
s=0x819060
start=0x400a1d:bye
length=0x3
tc.v=0x7b
tc.w=0x0
func.ptr=0x7b
func.sig_index=0x1c8
table.limits->initial=0x7b
table.limits->max=0x1c8
table.limits->has_max=0x1
```

# Run using valgrind
```
$ make vg
clang -O0 -g --std=c++14 -Weverything -Wno-padded -Wno-format-pedantic -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c99-extensions  -DDBG=0   -x c++ -c si.cc -o si.o
objdump -S -M x86_64,intel si.o > si.asm
clang -O0 -g --std=c++14 -Weverything -Wno-padded -Wno-format-pedantic -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c99-extensions  -DDBG=0   -x c++ -c Structure.cc -o Structure.o
objdump -S -M x86_64,intel Structure.o > Structure.asm
clang -lstdc++ -lm si.o Structure.o -o si
valgrind --leak-check=yes --track-origins=yes ./si
==30749== Memcheck, a memory error detector
==30749== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==30749== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==30749== Command: ./si
==30749== 
sizeof(Structrue)=0x28
s=0x601050
start=(nil):(null)
length=0x0
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
table.limits->has_max=0x0
s=0x6010a0
start=(nil):(null)
length=0x1
tc.v=0x0
tc.w=0x0
func.ptr=(nil)
...
func.sig_index=0x0
table.limits->initial=0x0
table.limits->max=0x0
table.limits->has_max=0x0
s=0x5aa0130
start=0x400a1d:bye
length=0x3
tc.v=0x7b
tc.w=0x0
func.ptr=0x7b
func.sig_index=0x1c8
table.limits->initial=0x7b
table.limits->max=0x1c8
table.limits->has_max=0x1
==30749== 
==30749== HEAP SUMMARY:
==30749==     in use at exit: 0 bytes in 0 blocks
==30749==   total heap usage: 4 allocs, 4 frees, 73,808 bytes allocated
==30749== 
==30749== All heap blocks were freed -- no leaks are possible
==30749== 
==30749== For counts of detected and suppressed errors, rerun with: -v
==30749== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
