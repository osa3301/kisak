target_sources(kisak PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/kisak.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/kisak.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/kdebug.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/kdebug.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/gamelib.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/gamelib.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/iface.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/iface.cpp"
)

add_subdirectory("main")

if(WIN32)
	add_subdirectory("windows")
endif()