set(EXE_NAME cli)
add_executable(${EXE_NAME})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
