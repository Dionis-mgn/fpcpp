project(fpcpp_examples)

macro(add_example name)
	add_executable(${name} "${name}.cpp")

	set_target_properties(${name}
		PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
		LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
		RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
	)
endmacro()

add_example(splitkeywords)
add_example(pipe)
add_example(curry)
