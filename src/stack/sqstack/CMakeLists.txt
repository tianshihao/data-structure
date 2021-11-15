add_library(sqstack STATIC
    sqstack.c
)

set_target_properties(sqstack PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(sqstack PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/stack/sqstack
    ${CMAKE_HOME_DIRECTORY}/include
)
