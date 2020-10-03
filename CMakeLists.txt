cmake_minimum_required(VERSION 3.0) # Guessed, should be updated in the future

project(kisak)

set(KISAK_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

# TODO: Make sure release binaries are stripped and display a warning for debug builds

# GCC: Special flags to build 32-bit
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

# Windows DLL injector
if(WIN32)
	set(KISAK_BUILD_INJECTOR TRUE CACHE BOOL "Build DLL injector")

	if(KISAK_BUILD_INJECTOR)
		add_executable(injector
			"${KISAK_SRC_DIR}/tool/injector.c"
		)
	endif()
endif()

# Memory library
add_library(kisak-mem STATIC)
add_subdirectory("${KISAK_SRC_DIR}/mem")

# SDK library
add_library(kisak-sdk INTERFACE)
target_include_directories(kisak-sdk INTERFACE
	"${KISAK_SRC_DIR}/sdk/include"
)

# ImGui
add_library(kisak-imgui STATIC)
add_subdirectory("${KISAK_SRC_DIR}/imgui")

# Kisak shared library
add_library(kisak SHARED)
add_subdirectory("${KISAK_SRC_DIR}/kisak")
target_link_libraries(kisak PRIVATE
	kisak-mem
	kisak-sdk
	kisak-imgui
)
