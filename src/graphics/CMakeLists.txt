target_sources(kisak PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/graphics.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/graphics.cpp"
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
