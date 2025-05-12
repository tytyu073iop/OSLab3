cmake_minimum_required(VERSION 4.0)

project(OSLab3)

add_executable(app main.cpp)

set(CXX_STANDARD "23")
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

add_library(maker maker.cpp globals.cpp)

target_include_directories(maker PUBLIC ${CMAKE_HOME_DIRECTORY})

target_link_libraries(app maker)

target_compile_features(app PRIVATE cxx_std_20)
target_compile_features(maker PRIVATE cxx_std_20)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin")