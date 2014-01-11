
#include "Ffi.hpp"

#include <utility>

namespace rme {

Ffi::Ffi(const std::string &libName) : library (libName){
    typeInfoToFfiType.insert(std::make_pair(typeid(int).name(),&ffi_type_sint));
}

Return<ffi_type*> Ffi::translateBoostAnyTypeToFfiType(const Any &data) {
    TypeInfoToFfiType::const_iterator it = typeInfoToFfiType.find(data.getType().name());
    if (it != typeInfoToFfiType.end()) {
        return (it->second);
    } else {
        return -1; 
    }
}

bool Ffi::fillArgs(std::vector<ffi_type*>        *ffiAgrsType,
                   std::vector<void*>           *ffiValues,
                   const std::list <Any> &argsList) {

    int i = 0;
    for (std::list<Any>::const_iterator 
             it = argsList.begin() , end = argsList.end() ;
         it != end ; ++it) {

        Return<ffi_type*> r = translateBoostAnyTypeToFfiType(*it);
        if (r.success){
            (*ffiAgrsType)[i] = r.data;
            (*ffiValues)[i]   = it->getPtr();
        } else {
            return false;
        }
        i++;
    }
    return true;
}

typedef void *F(void *);

bool Ffi::callOnMe (const std::string &functionName, 
                    Any returnValue,
                    const std::list <Any> &argsList) {

    ffi_cif cif;

    std::vector<ffi_type*> ffiAgrsType(argsList.size());
    std::vector<void*>    ffiValues  (argsList.size());

    
    if (!fillArgs(&ffiAgrsType, &ffiValues, argsList)) {
        std::cout << "Could not parse args" << std::endl;
        return false;
    }

    void *function = library.getFunction(functionName);

    if (function == NULL) {
        std::cerr << "Failed to get function" << std::endl;
        return false;
    }


    Return<ffi_type*> returnType = translateBoostAnyTypeToFfiType(returnValue);

    if (!returnType.success){
        return false;
    }


    if (ffi_prep_cif(&cif, 
                     FFI_DEFAULT_ABI, 
                     ffiAgrsType.size(),
                     returnType.data, 
                     ffiAgrsType.data()) == FFI_OK)  {
        
        ffi_call(&cif, 
                 (void (*)(void))(function), 
                 returnValue.getPtr(), 
                 ffiValues.data());
    } else {
        return false;
    }

    return true;
}

} // rme










