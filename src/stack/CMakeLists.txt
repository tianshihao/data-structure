project(stack)

add_executable(${PROJECT_NAME} program.c)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(${PROJECT_NAME} PUBLIC
   sqstack
   linkstack
)

add_subdirectory(sqstack)
add_subdirectory(linkstack)
