add_library (chapter3
   STATIC
   sqstack.c
)

set_target_properties(chapter3 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")

add_executable(program3 program3.c)

set_target_properties(program3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(program3
   PUBLIC
   chapter3
)
