project(ToolsLib)
cmake_minimum_required(VERSION 3.4.1)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
set(CODE_PATH      ${CMAKE_SOURCE_DIR}/src)
set(BUILDCACHE_PATH         ${CMAKE_SOURCE_DIR}/buildcache)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/output)
set(LIBRARY_OUTPUT_PATH     ${CMAKE_SOURCE_DIR}/lib)
set(PLATFORM_PATH           ${CMAKE_SOURCE_DIR}/Platform)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS   "-Wall -g")
set(CMAKE_CXX_FLAGS "-Wall -g")
include_directories(${PLATFORM_PATH}/inc/public_func)
add_executable(${TARGET_NAME})
add_subdirectory(${CODE_PATH})


file(GLOB PUBLIC_LIBS ${PLATFORM_PATH}/lib/*.a)

target_link_libraries(${TARGET_NAME} ${PUBLIC_LIBS} pthread)
