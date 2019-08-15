cmake_minimum_required (VERSION 3.5)

project (Max)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -Werror -Wextra -std=c11")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.c")

add_executable (Max ${source_files})
