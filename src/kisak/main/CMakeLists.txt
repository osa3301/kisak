if(WIN32)
	target_sources(kisak PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/main_win.cpp"
	)
endif()