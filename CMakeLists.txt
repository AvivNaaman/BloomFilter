cmake_minimum_required(VERSION 3.17)
project(14 C)

set(CMAKE_C_STANDARD 99)

# example usage
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(14 main.c murmur.c murmur.h table.c table.h )
add_executable(stats stats.c murmur.c murmur.h table.c table.h )