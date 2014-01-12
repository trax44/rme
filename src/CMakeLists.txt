
add_executable(rme 
main.cpp
DLOpen.cpp
DLOpen.hpp
Ffi.cpp
Ffi.hpp
)

pkg_check_modules (FFI REQUIRED libffi)

target_link_libraries(rme ${FFI_LIBRARIES} -ldl)
include_directories(${FFI_INCLUDE_DIRS})
