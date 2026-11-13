cmake_minimum_required(VERSION 3.10)
project(matrix_list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(matrix STATIC src/matrix.cpp)
target_include_directories(matrix PUBLIC include)

add_library(list STATIC src/node.cpp src/list.cpp)
target_include_directories(list PUBLIC include)
target_link_libraries(list PUBLIC matrix)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE list matrix)


configure_file(text.txt ${CMAKE_BINARY_DIR}/text.txt COPYONLY)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE list matrix)
