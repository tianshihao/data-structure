add_library (chapter_2
   STATIC
   sqlist.c
)

set_target_properties(chapter_2 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")
