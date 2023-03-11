cmake_minimum_required(VERSION 3.10])
project(inifile_parser)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_executable(pg "program.cpp" "inifile_parser.h")