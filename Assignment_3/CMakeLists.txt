cmake_minimum_required(VERSION 3.5)
PROJECT(Assignment_3_Potts_Model CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
find_package(OpenMP)

if (OPENMP_FOUND)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCES src/Program.cc
			src/iocontrol.cc
			src/Properties.cc
			src/Lattice.cc)
	
include_directories(include)
include_directories(external)
			
set( EXECUTABLE_OUTPUT_PATH ..)
add_executable(Program.run ${SOURCES})

target_link_libraries(Program.run PRIVATE)

target_include_directories(Program.run PRIVATE) 
