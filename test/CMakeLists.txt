file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")
file(GLOB_RECURSE TEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

add_executable(run_test ${TEST_SRC_FILES})
target_link_libraries(run_test gtest)
add_test(UnitTests ${CMAKE_CURRENT_BINARY_DIR}/run_test)
