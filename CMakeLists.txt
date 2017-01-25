cmake_minimum_required(VERSION 2.8)

project(fpcpp)

set (CMAKE_CXX_STANDARD 14)

add_subdirectory("googletest")
add_subdirectory("rapidcheck")

include_directories(
	.
	./rapidcheck/include
	./rapidcheck/extras/gtest/include
)

set(SOURCES
	tests/main.cpp
	tests/map.cpp
)

add_executable(fpcpp_tests ${SOURCES})
target_link_libraries(fpcpp_tests gtest rapidcheck)
