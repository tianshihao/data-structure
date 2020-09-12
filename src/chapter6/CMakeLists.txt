add_subdirectory(bitree)
add_subdirectory(threadtree)
add_subdirectory(bstree)

add_executable(program6 program6.c)

set_target_properties(program6 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(program6
   PUBLIC
   bitree
   threadtree
   bstree
)
