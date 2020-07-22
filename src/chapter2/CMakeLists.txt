add_library (chapter2
   STATIC
   sqlist.c
   linklist.c
)

set_target_properties(chapter2 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")

add_executable(program2 program2.c)

set_target_properties(program2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(program2
   PUBLIC
   chapter2
)
