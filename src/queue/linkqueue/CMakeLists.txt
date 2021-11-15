add_library(linkqueue STATIC
    linkqueue.c
)

set_target_properties(linkqueue PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj"
)

target_include_directories(linkqueue PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/queue/linkqueue
    ${CMAKE_HOME_DIRECTORY}/include
)
