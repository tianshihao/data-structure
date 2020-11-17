add_library(threadtree STATIC
    threadtree.c
)

set_target_properties(threadtree PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
