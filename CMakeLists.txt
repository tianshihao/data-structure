# 本项目的 CMakeLists
cmake_minimum_required(VERSION 3.0)

project(data-structure)

# 设置编码集为GBK, 方便显示中文.
set (CMAKE_C_FLAGS  "-fexec-charset=GBK")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_SOURCE_DIR}/build                    )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug/bin  )

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)
