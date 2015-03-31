enable_language(ASM)

add_custom_command(OUTPUT boot.o 
									 COMMENT "Building boot.o for OS X ${CMAKE_CURRENT_LIST_DIR}/boot.o"
							 	 	 COMMAND as -o ${CMAKE_CURRENT_LIST_DIR}/boot.o ${CMAKE_CURRENT_LIST_DIR}/boot.s)

add_custom_target(boot DEPENDS boot.o)

install(FILES boot.o DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/libor)