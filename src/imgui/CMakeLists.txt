target_include_directories(kisak-imgui PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/include"
)

target_sources(kisak-imgui PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/imgui.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_demo.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_draw.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_widgets.cpp"
)

if(UNIX)
	target_sources(kisak-imgui PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/imgui_impl_opengl2.cpp"
	)
endif()
