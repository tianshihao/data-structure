add_subdirectory(mgraph)
add_subdirectory(algraph)

add_executable(program7 program7.c)

set_target_properties(program7 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(program7
    PUBLIC
    mgraph
)
