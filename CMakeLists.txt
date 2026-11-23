cmake_minimum_required(VERSION 3.24)
project(matrix_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)
