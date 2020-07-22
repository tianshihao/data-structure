add_subdirectory(chapter_2)

add_executable(main main.c)

set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(main
   PUBLIC
   chapter_2
)
