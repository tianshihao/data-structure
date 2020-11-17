project(linearlist)

add_executable(${PROJECT_NAME} program.c)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(src
   clinklist.c
   dclinklist.c
   dlinklist.c
   linklist.c
   slinklist.c
   sqlist.c
)

add_library(linearlist_dynamic SHARED
   ${src}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
   linearlist_dynamic
)
