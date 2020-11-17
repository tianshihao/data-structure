project(queue)

add_executable(${PROJECT_NAME} program.c)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(${PROJECT_NAME} PUBLIC
   sqqueue
   linkqueue
)

add_subdirectory(sqqueue)
add_subdirectory(linkqueue)
