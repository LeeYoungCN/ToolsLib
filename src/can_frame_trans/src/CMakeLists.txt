aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src CODE_SRCS)

target_sources(${LIB_NAME} PUBLIC ${CODE_SRCS})
target_include_directories(${LIB_NAME} PUBLIC inc)
