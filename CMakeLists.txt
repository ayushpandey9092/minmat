cmake_minimum_required(VERSION 3.16)
project(minimat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(minimat STATIC src/matrix.cpp)
target_include_directories(minimat PUBLIC include)

add_executable(minimat_demo src/main.cpp)
target_link_libraries(minimat_demo PRIVATE minimat)
