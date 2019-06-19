cmake_minimum_required(VERSION 3.6)
add_library(
        imgui STATIC
        imconfig.h
        imgui.cpp
        imgui.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_impl_glfw_gl3.cpp
        imgui_impl_glfw_gl3.h
        imgui_internal.h
        stb_rect_pack.h
        stb_textedit.h
        stb_truetype.h
        )
# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

if (APPLE)
        find_library(COCOA_LIBRARY Cocoa)
        find_library(OpenGL_LIBRARY OpenGL)
        find_library(IOKIT_LIBRARY IOKit)
        find_library(COREVIDEO_LIBRARY CoreVideo)
        SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)
target_link_libraries(imgui glfw ${GLEW_LIBRARIES})