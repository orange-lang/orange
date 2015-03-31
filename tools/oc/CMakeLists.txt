include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

AUX_SOURCE_DIRECTORY(${oc_SOURCE_DIR} OC_SOURCES) 

add_executable(oc ${OC_SOURCES})
target_link_libraries(oc gen ${llvm_libs})