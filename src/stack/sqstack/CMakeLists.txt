add_library(
    sqstack
    sqstack.c
)

set_target_properties(sqstack PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
