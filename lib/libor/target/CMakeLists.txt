enable_language(ASM)

set(objname "")
set(osname "")
set(pathname "")

if(${APPLE})
	set(objname "boot.o")
	set(osname "OS X")
	set(pathname "${CMAKE_CURRENT_LIST_DIR}/osx")
elseif(${UNIX})
	set(objname "boot.o")
	set(osname "Linux")
	set(pathname "${CMAKE_CURRENT_LIST_DIR}/linux")
elseif(${WIN32})
	set(objname "boot.obj")
	set(osname "Windows")
	set(pathname "${CMAKE_CURRENT_LIST_DIR}/windows")
endif()

add_custom_command(OUTPUT ${objname}
									 COMMENT "Building ${objname} for ${osname} ${CMAKE_CURRENT_LIST_DIR}/${objname}"
								 COMMAND as -o ${CMAKE_CURRENT_LIST_DIR}/${objname} ${pathname}/boot.s)

add_custom_target(boot DEPENDS ${objname})
set_target_properties (boot PROPERTIES FOLDER lib)

install(FILES ${objname} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/libor)
