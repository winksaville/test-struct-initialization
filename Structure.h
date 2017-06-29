#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "si.h"

#include <cstdint>

struct Structure {
    const char* start;
    size_t length;

    union {
        TwoChars tc;
        Func func;
        MtLimits table;
        MtLimits memory;
        Global global;
    };

    //~Structure();
    //Structure() = default;
    //Structure(Structure& src);
    //static Structure& make();

    void display();
};

#endif
