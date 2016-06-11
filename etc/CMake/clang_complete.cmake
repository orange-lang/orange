##
## Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##

# Builds a .clang_complete file at the top-level directory.

macro(subdirlist result curdir)
	file(GLOB_RECURSE children RELATIVE ${curdir} "CMakeLists.txt")
	set(dirlist "")

	foreach(child ${children})
		get_filename_component(parent ${curdir}/${child} DIRECTORY)
		list(APPEND dirlist ${parent})
	endforeach()

	set(${result} ${dirlist})
endmacro()

macro(clang_complete path)
	set(flaglist "")

	# Go through all of the subdirectories with CMakeLists...
	subdirlist(DIRS ${CMAKE_SOURCE_DIR})
	foreach (dir ${DIRS})
		if (NOT IS_DIRECTORY ${dir})
			continue()
		endif()

		# Get the include direcotires...
		get_property(include_dirs DIRECTORY ${dir} PROPERTY INCLUDE_DIRECTORIES)
		foreach(dir ${include_dirs})
			list(APPEND flaglist "-I${dir}\n")
		endforeach()

		# And the definitions...
		get_property(defs DIRECTORY ${dir} PROPERTY COMPILE_DEFINITIONS)
		foreach(def ${defs})
			list(APPEND flaglist "-D${def}\n")
		endforeach()
	endforeach()

	# Do the other flags...
	set(FLAG_LIST ${CMAKE_CXX_FLAGS})
	separate_arguments(FLAG_LIST)

	set(DEF_LIST ${CXX_DEFINES})
	separate_arguments(DEF_LIST)

	foreach (flag ${FLAG_LIST})
		list(APPEND flaglist "${flag}\n")
	endforeach()

	foreach (def ${DEF_LIST})
		list(APPEND flaglist "${def}\n")
	endforeach()

	list(REMOVE_DUPLICATES flaglist)

	file(WRITE ${path} "")
	foreach(flag ${flaglist})
		file(APPEND ${path} "${flag}")
	endforeach()
endmacro()
