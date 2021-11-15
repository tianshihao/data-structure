project(stack)

add_executable(${PROJECT_NAME} main.c)

set_target_properties(${PROJECT_NAME} PROPERTIES 
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
   sqstack
   linkstack
)

target_include_directories(${PROJECT_NAME} PUBLIC
   ${CMAKE_HOME_DIRECTORY}/include/stack
   ${CMAKE_HOME_DIRECTORY}/include
)

add_subdirectory(sqstack)
add_subdirectory(linkstack)
