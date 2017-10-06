cmake_minimum_required(VERSION 3.0)
PROJECT(Assignment_1_FPU CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3")

set(SOURCES src/forces.cc
			src/integrators.cc
			src/properties.cc
			src/Program.cc)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})		
include_directories(include)
include_directories(external)
			
set( EXECUTABLE_OUTPUT_PATH ..)
add_executable(Program.run ${SOURCES})

target_link_libraries(Program.run PRIVATE ${MPI_C_LIBRARIES})
