set(PBC_UTIL_LIB pbc_util)
# add the library that runs
file(GLOB PBC_UTIL_LIB_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_library(${PBC_UTIL_LIB} STATIC ${PBC_UTIL_LIB_SRC_FILES})
# add_library(${PBC_UTIL_LIB} STATIC timer.cc)

target_include_directories(${PBC_UTIL_LIB}
                           INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include>
                           )

target_link_libraries(${PBC_UTIL_LIB} PUBLIC ${PBC_COMPILE_FLAGS})

# install rules
set(installable_libs ${PBC_UTIL_LIB} ${PBC_COMPILE_FLAGS})
install(TARGETS ${installable_libs}
        DESTINATION lib)
file(GLOB PBC_UTIL_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
install(FILES ${PBC_UTIL_HEADER_FILES} DESTINATION include)
