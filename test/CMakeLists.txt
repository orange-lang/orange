add_executable(oc_tester oc_tester.cc)
add_executable(test_lexer test_lexer.cc)

target_link_libraries(test_lexer gen helper)

file(GLOB files "files/*.or")
foreach(file ${files})
	get_filename_component(the_name ${file} NAME_WE) 

	add_test(
		NAME lex_${the_name}
		COMMAND test_lexer ${file} ${CMAKE_CURRENT_SOURCE_DIR}/baselines/
	)

	add_test(
		NAME ${the_name}
		COMMAND oc ${file} -o ${the_name}
	)

	add_test(
		NAME run_${the_name}
		COMMAND oc_tester ${CMAKE_BINARY_DIR}/test/${the_name}
	)
endforeach()