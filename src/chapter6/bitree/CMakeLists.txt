add_library(
    bitree
    bitree.c
    sqstack.c
    sqqueue.c
)

set_target_properties(bitree PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
