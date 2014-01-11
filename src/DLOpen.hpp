#ifndef RME_DLOPEN_H_
#define RME_DLOPEN_H_

#include <dlfcn.h>

namespace rme {


class DLOpen {

private:
    void *handler;
public:
    DLOpen(const std::string &libPath);
    void *getFunction (const std::string & functionName);
    ~DLOpen();
};

} // rme

#endif /* RME */
