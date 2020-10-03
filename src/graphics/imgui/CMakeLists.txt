target_sources(kisak PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/imconfig.h"
	"${CMAKE_CURRENT_LIST_DIR}/imgui.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/imgui.h"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_demo.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_draw.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_internal.h"
	"${CMAKE_CURRENT_LIST_DIR}/imgui_widgets.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/imstb_rectpack.h"
	"${CMAKE_CURRENT_LIST_DIR}/imstb_textedit.h"
	"${CMAKE_CURRENT_LIST_DIR}/imstb_truetype.h"

)

if(WIN32)
	target_sources(kisak PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/imgui_impl_dx9.h"
		"${CMAKE_CURRENT_LIST_DIR}/imgui_impl_dx9.cpp"
	)
endif()

if(UNIX)
	target_sources(kisak PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/imgui_impl_opengl2.h"
		"${CMAKE_CURRENT_LIST_DIR}/imgui_impl_opengl2.cpp"
	)
endif()
