add_library(sqqueue STATIC
    sqqueue.c
)

set_target_properties(sqqueue PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(sqqueue PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/queue/sqqueue
    ${CMAKE_HOME_DIRECTORY}/include
)
