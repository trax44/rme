#include <iostream>

#include "Ffi.hpp"

int main (int argc, char *argv[]){
    
    rme::Ffi ffi ("../test/libtest.so");
    std::list<rme::Any> emptyList;
    int r;
    rme::Any returnValueContainer (&r);


    if (!ffi.callOnMe("_Z13func_Int_Voidv", returnValueContainer, emptyList)){
        return -1;
    }
    std::cout << "returned> "  << *(static_cast<int *>(returnValueContainer.getPtr())) << std::endl;
    
    return 0;
}
