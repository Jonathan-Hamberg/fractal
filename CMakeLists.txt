cmake_minimum_required ( VERSION 3.3 )
project( fractal )

set (CMAKE_CXX_STANDARD 11)

include_directories ( ${CMAKE_SOURCE_DIR}/src/ )

set ( SOURCE
    src/main.cpp
    src/imgui.cpp
    src/imgui_draw.cpp
    src/imgui_impl_glfw_gl3.cpp
    src/glad/glad.c
    src/shader.cpp
    src/texture.cpp
    src/gui.cpp )
    
add_executable ( fractal ${SOURCE} )

if(WIN32)
	file( COPY ${CMAKE_SOURCE_DIR}/lib/glfw3.dll DESTINATION ${CMAKE_SOURCE_DIR}/bin/ )
	target_link_libraries( fractal ${CMAKE_SOURCE_DIR}/lib/glfw3dll.lib )
else(WIN32)
	target_link_libraries( fractal ${GLFW3_LIBRARY} dl X11 Xrandr Xi pthread Xinerama Xcursor )
endif(WIN32)	

