project(linearlist)

add_executable(${PROJECT_NAME} main.c)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(${PROJECT_NAME} PUBLIC
   linklist
   sqlist
)

add_subdirectory(linklist)
add_subdirectory(sqlist)