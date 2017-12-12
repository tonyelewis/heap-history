cmake_minimum_required (VERSION 3.5.2)

find_package(Boost 1.60 REQUIRED )

# Compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
add_compile_options(
	-W
	-Wall
	-Werror
	-Wextra
	-Wcast-qual
	-Wconversion
	-Wformat=2
	-Wnon-virtual-dtor
	-Wshadow
	-Wsign-compare
	-Wsign-conversion
	-pedantic
	-ftabstop=2
	$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_GREATER:$<CXX_COMPILER_VERSION>,6.0.0>>:-Wduplicated-cond>
	$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_GREATER:$<CXX_COMPILER_VERSION>,7.0.0>>:-Wduplicated-branches>
	$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_GREATER:$<CXX_COMPILER_VERSION>,7.0.0>>:-Wrestrict>
)

# In debug mode, append GCC compiler flags with -D_GLIBCXX_DEBUG
add_compile_options( $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:DEBUG>>:-D_GLIBCXX_DEBUG> )

# Add colour diagnostics when using Clang with Ninja
if ( CMAKE_GENERATOR STREQUAL "Ninja" )
	add_compile_options( $<$<CXX_COMPILER_ID:Clang>:-fcolor-diagnostics> )
endif()

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY .. )

add_subdirectory( source )
