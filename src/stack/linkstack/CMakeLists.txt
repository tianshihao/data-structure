add_library(linkstack STATIC
    linkstack.c
)

set_target_properties(linkstack PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(linkstack PUBLIC
    ${CMAKE_HOME_DIRECTORY}/include/stack/linkstack
    ${CMAKE_HOME_DIRECTORY}/include
)
