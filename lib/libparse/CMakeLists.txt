set(FLEX_FlexOutput_OUTPUTS "")
set(BISON_BisonOutput_OUTPUTS "")

find_package(BISON)
if (${BISON_FOUND})
    bison_target(BisonOutput ${CMAKE_SOURCE_DIR}/lib/libparse/parser.y ${CMAKE_SOURCE_DIR}/lib/libparse/parser.cc)
endif()

find_package(FLEX)
if (${FLEX_FOUND})
    flex_target(FlexOutput ${CMAKE_SOURCE_DIR}/lib/libparse/lexer.l ${CMAKE_SOURCE_DIR}/lib/libparse/lexer.cc)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/lib/libparse)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib/libparse LIBPARSE_SOURCES)

file(GLOB SRC_INCLUDES)
file(GLOB INCLUDES "${CMAKE_SOURCE_DIR}/include/libparse/*.h")

source_group(parser FILES
	${CMAKE_SOURCE_DIR}/lib/libparse/parser.y
	${CMAKE_SOURCE_DIR}/lib/libparse/lexer.l
)

source_group(parser\\generated FILES
    ${FLEX_FlexOutput_OUTPUTS} ${BISON_BisonOutput_OUTPUTS}
)

source_group(src FILES ${LIBPARSE_SOURCES})

source_group(headers FILES ${INCLUDES})

add_library(parse ${LIBPARSE_SOURCES} ${INCLUDES} 	${FLEX_FlexOutput_OUTPUTS}
	${BISON_BisonOutput_OUTPUTS}
	${CMAKE_SOURCE_DIR}/lib/libparse/lexer.l
	${CMAKE_SOURCE_DIR}/lib/libparse/parser.y
)

set_target_properties (parse PROPERTIES FOLDER lib)

cotire(parse)

target_link_libraries(parse ast)
add_dependencies(parse ast)
