cmake_minimum_required(VERSION 3.5)

project(pbc_test)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cc ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
link_libraries(${PROJECT_NAME} ${PBC_EXEC_LIB_PATH})

set(EXECUTABLE_OUTPUT_PATH "${PBC_BIN_OUTPUT_PATH}")
