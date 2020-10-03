target_sources(kisak PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/module.hpp"
)

if(WIN32)
	target_sources(kisak PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/module_win.cpp"
	)
endif()

if(UNIX)
	target_sources(kisak PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/module_linux.cpp"
	)
endif()
