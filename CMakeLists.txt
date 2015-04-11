cmake_minimum_required (VERSION 2.6)
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

# This gets prepdended to all CXX_FLAGS_* strings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Use this for debugging with valgrind.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")

PROJECT(TracedNeighbors)

# The version number.
set (TraceHBonds_VERSION_MAJOR 0)
set (TraceHBonds_VERSION_MINOR 9)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/config/TracedNeighborsConfig.h.in"
	"${PROJECT_BINARY_DIR}/TracedNeighborsConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find TraceHBondsConfig.h
include_directories("${PROJECT_BINARY_DIR}")

if( CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message( "Making static binary." )
	set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
endif()

add_subdirectory(src)

option(GTESTS "Compile with gtest unit tests." OFF)

if ( GTESTS )
	include(CTest)
	add_subdirectory(test)
endif( GTESTS )

