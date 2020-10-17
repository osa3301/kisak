target_sources(kisak PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/module.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/module.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/vtable.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/hook.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/hook.cpp"
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
