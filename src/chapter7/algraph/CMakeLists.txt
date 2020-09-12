add_library(
    algraph
    algraph.c
)

set_target_properties(algraph PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
