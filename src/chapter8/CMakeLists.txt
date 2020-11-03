add_library(
    sort
    sort.c
)

set_target_properties(sort PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")

add_executable(program8 program8.c)

set_target_properties(program8 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(
    program8
    PUBLIC
    sort
)