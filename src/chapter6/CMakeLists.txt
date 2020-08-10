add_library (chapter6
   STATIC
   bitree.c
   sqstack.c
   sqqueue.c
   threadtree.c
)

set_target_properties(chapter6 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")

add_executable(program6 program6.c)

set_target_properties(program6 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(program6
   PUBLIC
   chapter6
)
