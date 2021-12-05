add_library(mgraph STATIC
    mgraph.c
    sqqueue.c
    sqstack.c
)

set_target_properties(mgraph PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(mgraph PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/graph/mgraph
    ${CMAKE_HOME_DIRECTORY}/include/graph
    ${CMAKE_HOME_DIRECTORY}/include
)