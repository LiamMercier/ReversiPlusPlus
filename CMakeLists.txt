# This is likely not the minimum required, but it is the
# current version. Edit if needed.
cmake_minimum_required(VERSION 3.25)

project(ReversiPlusPlus CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

add_executable(ReversiPlusPlus Main.cpp ReversiBoard.h ReversiBoard.cpp)

target_link_libraries(ReversiPlusPlus stdc++)
