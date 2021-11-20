add_library(bstree STATIC
    bstree.c
)

set_target_properties(bstree PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(bstree PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/tree/bstree
    ${CMAKE_HOME_DIRECTORY}/include
)
