#ifndef RME_ANY_H_
#define RME_ANY_H_

#include <typeinfo>
#include <string>

namespace rme {

class Any {
private:
    void *ptr;
    const std::type_info &type;

public:
    template<typename ValueType>
    Any(ValueType *value) : 
        ptr(reinterpret_cast<void*> (value)),
        type (typeid(*value)){}
  
    const std::string getTypeName() const{
        return type.name();
    }
    const std::type_info& getType() const{
        return type;
    }

    void *getPtr() const{
        return ptr;
    }
};




} // rme


#endif /* RME */
