cmake_minimum_required(VERSION 3.1.0)

project(Simq CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE SimQLib)

target_include_directories(main PRIVATE include)
