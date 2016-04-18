cmake_minimum_required(VERSION 3.5)
project(ElfReader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ELFREADER_SRC common.cpp )
set(SOURCE_FILES ${ELFREADER_SRC} main.cpp)
add_executable(ElfReader ${SOURCE_FILES})