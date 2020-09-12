add_library(
    mgraph
    mgraph.c
    sqqueue.c
)

set_target_properties(mgraph PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
