project(fpcpp_tests)

set(SOURCES
	main.cpp
	map.cpp
)

add_executable(fpcpp_tests ${SOURCES})
target_link_libraries(fpcpp_tests gtest rapidcheck)

set_target_properties( fpcpp_tests
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
	LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)
