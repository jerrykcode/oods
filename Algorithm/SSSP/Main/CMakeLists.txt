cmake_minimum_required(VERSION 2.6)
project(sssp)
add_executable(sssp main.cpp
		   ../pathRecorder.cpp)
include_directories(../)
include_directories(../../../Graph/)
