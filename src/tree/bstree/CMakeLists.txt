add_library(bstree STATIC
    bstree.c
)

set_target_properties(bstree PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
