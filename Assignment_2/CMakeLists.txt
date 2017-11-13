cmake_minimum_required(VERSION 3.0)
PROJECT(Assignment_2_SE CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")

set(SOURCES src/potentials.cc
			src/Program.cc)
	
include_directories(include)
include_directories(external)
			
set( EXECUTABLE_OUTPUT_PATH ..)
add_executable(Program.run ${SOURCES})

target_link_libraries(Program.run PRIVATE)

target_include_directories(Program.run PRIVATE) 
