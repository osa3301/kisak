if(WIN32)
	target_sources(kisak-mem PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/module_win.cpp"
	)
endif()

target_include_directories(kisak-mem PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/include"
)