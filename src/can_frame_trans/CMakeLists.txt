set(EXE_NAME can_frame_tran)
set(LIB_NAME can_frame_trans_lib)

add_library(${LIB_NAME})
add_executable(${EXE_NAME})

add_subdirectory(src)
add_subdirectory(main)

target_link_libraries(${EXE_NAME} ${LIB_NAME})
target_link_libraries(${LIB_NAME} ${PUBLIC_LIBS} pthread)
