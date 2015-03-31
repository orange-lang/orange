include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(llvm_libs all)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

AUX_SOURCE_DIRECTORY(${oc_SOURCE_DIR} OC_SOURCES) 

file(GLOB_RECURSE INCLUDES "${CMAKE_SOURCE_DIR}/*.h")

add_executable(oc ${OC_SOURCES} ${INCLUDES})
target_link_libraries(oc gen helper ${llvm_libs})
ADD_DEPENDENCIES(oc boot)

install(TARGETS oc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)