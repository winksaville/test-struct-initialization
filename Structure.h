#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "si.h"

#include <cstdint>
#include <string>

struct Structure {
    std::string s;

    union {
        TwoChars tc;
        Func func;
        MtLimits table;
        MtLimits memory;
        Global global;
    };

    ~Structure() {}
    Structure() { ZeroMemory(*this); }
    //Structure(Structure& src);
    //static Structure& make();

    void display();
};

#endif
