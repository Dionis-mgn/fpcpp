cmake_minimum_required(VERSION 2.8)

project(fpcpp)

set (CMAKE_CXX_STANDARD 14)

add_subdirectory("googletest")
add_subdirectory("rapidcheck")

include_directories(
	./include
	./rapidcheck/include
	./rapidcheck/extras/gtest/include
)

set (BIN_DIR "${PROJECT_SOURCE_DIR}/bin")

add_subdirectory(tests)
add_subdirectory(examples)
