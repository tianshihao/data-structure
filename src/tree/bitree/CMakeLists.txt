﻿add_library(bitree STATIC
    bitree.c
    sqstack.c
    sqqueue.c
)

set_target_properties(bitree PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(bitree PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/tree/bitree
    ${CMAKE_HOME_DIRECTORY}/include
)
