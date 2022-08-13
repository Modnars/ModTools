cmake_minimum_required(VERSION 3.15)

# set the compile flags
set(PBC_COMPILE_FLAGS  pbc_compile_flags)
add_library(${PBC_COMPILE_FLAGS} INTERFACE)
target_compile_features(${PBC_COMPILE_FLAGS} INTERFACE cxx_std_17)
target_compile_options(${PBC_COMPILE_FLAGS} INTERFACE "-Werror;-Wall;-Wunused")

# configure a header file to pass the version number only
configure_file(pbc_info.h.in pbc_info.h)

# add the pbc_util library
add_subdirectory(util)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} 
        ${PROTOBUF_LIB_PATH}/libprotobuf.a
        pthread
        )

# for pbc_info.h
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}/src" PUBLIC "${PROTOBUF_INCLUDE_PATH}")

# add the install targets
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/src/pbc_info.h"
        DESTINATION include
        )

