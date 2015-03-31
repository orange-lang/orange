add_executable(oc_tester main.cc)

file(GLOB files "files/*.or")
foreach(file ${files})
	get_filename_component(the_name ${file} NAME_WE) 
	add_test(
		NAME ${the_name}
		COMMAND oc ${file} -o ${the_name}
	)
	add_test(
		NAME run_${the_name}
		COMMAND oc_tester ${CMAKE_BINARY_DIR}/test/${the_name}
	)
endforeach()