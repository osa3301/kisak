target_sources(kisak PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/kisak.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/kisak.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/kdebug.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/kdebug.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/gamemodule.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/gamemodule.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/iface.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/iface.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ui.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/ui.cpp"
)

add_subdirectory("main")
add_subdirectory("mem")
add_subdirectory("graphics")
