cmake_minimum_required(VERSION 3.6)
project(projv3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Werror -Wextra -Wall -pedantic")

set(SOURCE_FILES proj1.c)
add_executable(projv3 ${SOURCE_FILES})