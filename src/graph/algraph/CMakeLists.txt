add_library(algraph STATIC
    algraph.c
    sqqueue.c
)

set_target_properties(algraph PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(algraph PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/graph/algraph
    ${CMAKE_HOME_DIRECTORY}/include/graph
    ${CMAKE_HOME_DIRECTORY}/include
)
