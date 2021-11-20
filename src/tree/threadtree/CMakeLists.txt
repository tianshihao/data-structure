add_library(threadtree STATIC
    threadtree.c
)

set_target_properties(threadtree PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(threadtree PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/tree/threadtree
    ${CMAKE_HOME_DIRECTORY}/include
)
