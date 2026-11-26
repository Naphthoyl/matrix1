add_library(node STATIC node.cpp)
target_link_libraries(node PUBLIC matrix matrix_headers)
