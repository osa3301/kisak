cmake_minimum_required(VERSION 3.0) # Guessed, should be updated in the future

project(kisak)

set(KISAK_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

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

# Kisak shared library
add_library(kisak SHARED)
add_subdirectory("${KISAK_SRC_DIR}/kisak")
target_link_libraries(kisak PRIVATE
	kisak-mem
	kisak-sdk
)