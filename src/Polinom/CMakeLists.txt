file(GLOB_RECURSE polinom_src *.cpp)
add_library(polinom_lib STATIC "${POLINOM_H}" "${polinom_src}")