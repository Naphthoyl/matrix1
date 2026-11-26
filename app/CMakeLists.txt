include(FetchContent)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP ON)
FetchContent_MakeAvailable(Boost)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE list node matrix Boost::program_options)

if (MINGW)
    target_link_options(app PRIVATE -static -static-libgcc -static-libstdc++)
endif ()


configure_file(text.txt ${CMAKE_CURRENT_BINARY_DIR}/text.txt COPYONLY)
configure_file(config.cfg ${CMAKE_CURRENT_BINARY_DIR}/config.cfg COPYONLY)
