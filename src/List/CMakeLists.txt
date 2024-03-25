file(GLOB_RECURSE list_src *.cpp)
add_library(list_lib STATIC "${LIST_H}" "${list_src}")