#ifndef RME_FFI_H_
#define RME_FFI_H_

#include <ffi.h>
#include <string>
#include <list>
#include <vector>

#include <typeinfo>
#include "Return.hpp"

#ifdef RME_CPP11
#include <unordered_map>
using std::unordered_map;
#else
#include <tr1/unordered_map>
using std::tr1::unordered_map;
#endif

#include "DLOpen.hpp"
#include "Any.hpp"

namespace rme {

class Ffi {
public:
    typedef unordered_map<std::string,ffi_type*> TypeInfoToFfiType;

private:
    DLOpen library;
    TypeInfoToFfiType typeInfoToFfiType;

    Return<ffi_type*> translateBoostAnyTypeToFfiType(const Any &data);

    bool fillArgs(std::vector<ffi_type*>        *ffiAgrsType,
                  std::vector<void*>           *ffiValues,
                  const std::list <Any> &argsList) ;
    
public:
    Ffi(const std::string &libName);
    bool callOnMe (const std::string &functionName, 
                   Any returnValue,
                   const std::list <Any > &argsList);

};

} // rme

#endif /* RME */
