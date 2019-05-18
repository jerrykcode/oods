cmake_minimum_required(VERSION 2.8)
project(scc)
add_executable(scc main.cpp
		   ../tarjan.cpp)
include_directories(../)
include_directories(../../../Graph/)
