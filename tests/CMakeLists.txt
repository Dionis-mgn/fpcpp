project(fpcpp_tests)

set(SOURCES
	add.cpp
	all.cpp
	always.cpp
	any.cpp
	both.cpp
	complement.cpp
	curry.cpp
	divide.cpp
	equals.cpp
	F.cpp
	filter.cpp
	gt.cpp
	gte.cpp
	identity.cpp
	is_empty.cpp
	lt.cpp
	lte.cpp
	main.cpp
	map.cpp
	multiply.cpp
	not.cpp
	pipe.cpp
	reduce.cpp
	reject.cpp
	split.cpp
	subtract.cpp
	T.cpp
	tap.cpp
	trim.cpp
)

add_executable(fpcpp_tests ${SOURCES})
target_link_libraries(fpcpp_tests gtest rapidcheck)

set_target_properties( fpcpp_tests
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}
	LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
	RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)
