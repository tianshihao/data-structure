add_library(mgraph STATIC
    mgraph.c
    sqqueue.c
    sqstack.c
)

set_target_properties(mgraph PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
