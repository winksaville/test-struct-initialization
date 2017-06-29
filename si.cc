#include "Structure.h"

#include <cstddef>
#include <cstring>

//extern Structure gs0;
//Structure gs0{};

//static Structure gs1{.length=1, .start=NULL};

//#define STRG "hi"
//static Structure gs2{.s=STRG, .table={.limits={0xAA, 0xBB, true}}};

int main(void) {
    // default ctor called but no default initialization is done
    printf("sizeof(Structrue)=0x%lx\n", sizeof(Structure));

    std::string s{"Hi wink"};
    printf("s=%s\n", s.c_str());

    s = "bye";
    printf("s=%s\n", s.c_str());

    //gs0.display();
    //gs1.display();
    //gs2.display();

    Structure s0;
    s0.display();

    Structure s1{};
    s1.display();

    //Error can't use aggregate initialize except empty as above
    //Structure s1{.table.limits.initial=123};
    //s1.display();

    // default ctor called and default initalization IS DONE??
    Structure* s2 = new Structure();
    s2->display();

    //Structure* s3 = new Structure{.length=strlen(s), .start=s, .table={.limits={123, 456, true}}};
    //s3->display();

    delete s2;
    //delete s3;
}
