cmake_minimum_required(VERSION 3.14)
project(json_parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(json_parser main.cpp json/objects.cpp json/objects.h json/parsing.cpp json/parsing.h json/json.cpp json/json.h)