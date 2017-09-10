cmake_minimum_required(VERSION 2.6)
set (CMAKE_CXX_STANDARD 14)
 
add_executable(runTests.run tests.cc)

add_subdirectory("/mnt/c/MM837_Computational_Physics/Hypothesis_Test_Example/rapidcheck")
target_link_libraries(runTests.run rapidcheck)