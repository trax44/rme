find_package(PkgConfig)

add_executable(rme 
main.cpp
DLOpen.cpp
DLOpen.hpp
Ffi.cpp
Ffi.hpp
)

pkg_check_modules (FFI libffi)

target_link_libraries(rme ${FFI_LIBRARIES} -ldl)
include_directories(rme ${FFI_CFLAGS})
