#ifndef SI_H
#define SI_H

#include <cstdio>
#include <cstdint>

template<typename T>
void ZeroMemory(T& v) {
    __builtin_memset(&v, 0, sizeof(v));
}

enum class Type {
  I32 = -0x01,
  I64 = -0x02,
  F32 = -0x03,
  F64 = -0x04,
  Anyfunc = -0x10,
  Func = -0x20,
  Void = -0x40,
  ___ = Void, /* convenient for the opcode table in opcode.h */
  Any = 0,    /* Not actually specified, but useful for type-checking */
};

struct TwoChars {
    char v;
    char w;

    //TwoChars(): v(), w() {}
    //TwoChars(): w() { printf("TwoChars=%p\n", this); }
    //TwoChars(): v(1), w(2) { printf("TwoChars=%p\n", this); }
    //TwoChars(char a, char b): v(a), w(b) {}
};

struct Limits {
    uint64_t initial;
    uint64_t max;
    bool has_max;

    //Limits() : initial(), max(), has_max() {}
    //Limits() : initial(0), max(0), has_max(false) {}
    //Limits(uint64_t i, uint64_t m, bool h):
    //    initial(i), max(m), has_max(h) {
    //}
};

struct Func {
    const char* ptr;
    int sig_index;

    //Func() : ptr(), sig_index() {}
    //Func() : ptr(NULL), sig_index(0) {}
};

struct MtLimits {
    Limits limits;

    //MtLimits(): limits() {}
    //MtLimits() {}
    //MtLimits(uint64_t initial) : limits(initial, 2, true) {}
};

struct Global {
    Type type;
    bool mutable_;

    //Global() : type(), mutable_() {}
    //Global() : type(Type::Any), mutable_(false) {}
};

#endif
