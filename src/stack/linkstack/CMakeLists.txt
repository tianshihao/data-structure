add_library(
    linkstack
    linkstack.c
)

set_target_properties(linkstack PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
