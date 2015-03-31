enable_language(ASM)

add_custom_command(OUTPUT boot.obj 
									 COMMENT "Building boot.obj for Windows ${CMAKE_CURRENT_LIST_DIR}/boot.obj"
							 	 	 COMMAND as -o${CMAKE_CURRENT_LIST_DIR}/boot.obj ${CMAKE_CURRENT_LIST_DIR}/boot.s)

add_custom_target(boot DEPENDS boot.obj)

install(FILES boot.obj DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/libor)