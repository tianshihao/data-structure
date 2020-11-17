project(linearlist)

set(  src
   clinklist.c
   dclinklist.c
   dlinklist.c
   linklist.c
   slinklist.c
   sqlist.c
)

add_executable(${PROJECT_NAME} program.c ${src})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
