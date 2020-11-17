add_library(linkstack STATIC
    linkstack.c
)

set_target_properties(linkstack PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
