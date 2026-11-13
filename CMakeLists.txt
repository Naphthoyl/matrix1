cmake_minimum_required(VERSION 3.24)
project(matrix_list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP ON)
FetchContent_MakeAvailable(Boost)


add_library(matrix STATIC src/matrix.cpp)
target_include_directories(matrix PUBLIC include)

add_library(list STATIC src/node.cpp src/list.cpp)
target_include_directories(list PUBLIC include)
target_link_libraries(list PUBLIC matrix)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE list matrix Boost::program_options)

if (MINGW)
    target_link_options(app PRIVATE -static -static-libgcc -static-libstdc++)
endif()


add_executable(test test.cpp)
target_link_libraries(test PRIVATE list matrix)

configure_file(text.txt ${CMAKE_BINARY_DIR}/text.txt COPYONLY)
configure_file(config.cfg ${CMAKE_BINARY_DIR}/config.cfg COPYONLY)


