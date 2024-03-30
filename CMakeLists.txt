cmake_minimum_required(VERSION 3.20)

project(sem4_lab1)

set(CMAKE_CXX_STANDARD 17)

#enable_testing()

include_directories("include")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest)
add_subdirectory(gtest)

add_subdirectory(app)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
