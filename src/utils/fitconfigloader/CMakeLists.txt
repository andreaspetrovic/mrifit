cmake_minimum_required (VERSION 2.8)

project(fitconfigloader)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(SOURCE_WILDCARDS *.h *.H *.hpp *.hh *.hxx *.c *.C *.cpp *.cc *.cxx)
set(CMAKE_BUILD_TYPE Release)


add_executable(demo demo.cpp)
