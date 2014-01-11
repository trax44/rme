#include <stdexcept>

#include "DLOpen.hpp"

namespace rme {

DLOpen::DLOpen(const std::string &libPath) : handler (NULL) {
    if ((handler = dlopen(libPath.c_str(), RTLD_LAZY)) == NULL){
        throw std::runtime_error("Could not load library" );
    }
}



void *DLOpen::getFunction (const std::string & functionName) {
    return dlsym(handler, functionName.c_str());
}


DLOpen::~DLOpen(){
    if (handler != NULL){
        dlclose(handler);
    }
}

} // rem
