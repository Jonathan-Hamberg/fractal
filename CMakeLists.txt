macro(symlink filepath sympath)
    if(WIN32)
        file(TO_NATIVE_PATH ${filepath} filepath_native)
        file(TO_NATIVE_PATH ${sympath} sympath_native)
        set(cmd cmd.exe /c mklink /J ${sympath_native} ${filepath_native})
    else(WIN32)
        set(cmd ln -s ${filepath} ${sympath})
    endif(WIN32)
    execute_process(COMMAND ${cmd} )
endmacro(symlink)

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
    src/mandlebrot.cpp
    src/util.cpp
    src/gui.cpp )

add_executable ( fractal ${SOURCE} )

if(WIN32)
    file( COPY ${CMAKE_SOURCE_DIR}/lib/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR} )
    target_link_libraries( fractal ${CMAKE_SOURCE_DIR}/lib/glfw3dll.lib )
else(WIN32)
    find_package(glfw3 3.1 REQUIRED)
    target_link_libraries( fractal ${GLFW3_LIBRARY} dl X11 Xrandr Xi pthread Xinerama Xcursor )
endif(WIN32)

symlink("${CMAKE_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/res" )
