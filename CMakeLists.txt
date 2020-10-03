cmake_minimum_required(VERSION 3.0) # Guessed, should be updated in the future

project(kisak)

set(KISAK_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

# Set target game
set(KISAK_GAME "Team Fortress 2" CACHE STRING "Target Game")
set_property(CACHE KISAK_GAME PROPERTY STRINGS 
	"Team Fortress 2"
)
set(KISAK_AGGRESSIVE_LOGGING TRUE CACHE BOOL "Log as much info as possible")

if(KISAK_GAME STREQUAL "Team Fortress 2")
	set(KISAK_TF2 TRUE)
endif()

# Detect OS
if(WIN32)
	set(KISAK_WIN32 TRUE)
endif()
if(UNIX AND NOT APPLE)
	set(KISAK_LINUX TRUE)
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
	message(AUTHOR_WARNING "You are building kisak in debug mode. This could result in an increased chance for VAC detection. Be advised.")
	set(KISAK_DEBUG TRUE)
endif()

# Generate kconfig.hpp
configure_file(
	"${KISAK_SRC_DIR}/kconfig.hpp.in"
	"${KISAK_SRC_DIR}/kconfig.hpp"
)

# Windows DLL injector
if(WIN32)
	set(KISAK_BUILD_INJECTOR TRUE CACHE BOOL "Build DLL injector")

	if(KISAK_BUILD_INJECTOR)
		add_executable(injector
			"${KISAK_SRC_DIR}/tool/injector.c"
		)
	endif()
endif()

# GCC: Special flags to build 32-bit
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

# Kisak shared library
add_library(kisak SHARED)
add_subdirectory("${KISAK_SRC_DIR}")
