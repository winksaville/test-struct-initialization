#include "Structure.h"

#include <cstdio>

#if 0
Structure::~Structure() {
    printf("dtor this=%p\n", this);
}

Structure::Structure()  {
    printf("ctor this=%p\n", this);
    //ZeroMemory(*this);
    this->tc = {};
}

Structure::Structure(Structure& src) {
    printf("copy ctor this=%p, src=%p\n", this, &src);
    __builtin_memcpy(this, &src, sizeof(*this));
}

Structure& Structure::make() {
    Structure* s = new Structure();
    return *s;
}
#endif

void Structure::display() {
    //assert(s.start == NULL);
    //assert(s.length == 456);
    //assert(s.func.ptr == NULL);
    //assert(s.func.sig_index == 1);

    printf("s=%p\n", this);
    printf("s=%p:%s\n", &this->s, this->s.length() != 0 ? this->s.c_str() : "Empty" );
    printf("length=0x%lx\n", this->s.length());
    printf("tc.v=0x%x\n", this->tc.v);
    printf("tc.w=0x%x\n", this->tc.w);
    printf("func.ptr=%p\n", this->func.ptr);
    printf("func.sig_index=0x%x\n", this->func.sig_index);
    printf("table.limits->initial=0x%lx\n", this->table.limits.initial);
    printf("table.limits->max=0x%lx\n", this->table.limits.max);
    printf("table.limits->has_max=0x%x\n", this->table.limits.has_max);
}
