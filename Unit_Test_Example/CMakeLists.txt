cmake_minimum_required(VERSION 2.6)
 
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(runTests.run tests.cc)
target_link_libraries(runTests.run ${GTEST_LIBRARIES} pthread)