file(GLOB_RECURSE TEST_PROGRAMS "${CMAKE_SOURCE_DIR}/unit/*.cc")

include_directories(${CMAKE_SOURCE_DIR}/include)

foreach(program ${TEST_PROGRAMS})
	get_filename_component(fileName ${program} NAME_WE)

	# Replace unit_ in filename with test (e.g., unit_cmd -> test-cmd)
	string(REPLACE "unit_" "test-" outputName ${fileName})

	add_executable(${outputName} ${program})
	cotire(${outputName})

	find_package(LLVM REQUIRED HINTS ${CMAKE_BINARY_DIR}/etc/llvm/cmake/modules/CMakeFiles)
	add_definitions(${LLVM_DEFINITIONS})

	set_target_properties(${outputName}
		PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)

	target_link_libraries(${outputName} util cmd testlib ast)
	add_dependencies(${outputName} util cmd testlib ast)
	set_target_properties (${outputName} PROPERTIES FOLDER unit)

	add_test(
		NAME ${outputName}
        COMMAND ${CMAKE_BINARY_DIR}/test/bin/${outputName}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)
endforeach()
