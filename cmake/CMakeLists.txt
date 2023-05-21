cmake_minimum_required(VERSION 3.25)
project(game_of_life)

set(CMAKE_CXX_STANDARD 20)

set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)
add_subdirectory(../source ${BINARY_DIR})

target_link_options(${PROJECT_NAME} PRIVATE -static)
