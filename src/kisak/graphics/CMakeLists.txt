if(WIN32)
endif()

if(UNIX)
	target_sources(kisak PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/graphics_linux.cpp"
	)
endif()

target_sources(kisak PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/graphics.cpp"
)
