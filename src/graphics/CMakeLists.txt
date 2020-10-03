target_sources(kisak PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/graphics.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/graphics.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_impl_source.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_impl_source.cpp"
)

if(WIN32)
	target_sources(kisak PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/graphics_win.cpp"
	)
endif()

if(UNIX)
	target_sources(kisak PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/graphics_linux.cpp"
	)
endif()

add_subdirectory("imgui")