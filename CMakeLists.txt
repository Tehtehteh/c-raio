cmake_minimum_required(VERSION 3.14)

project(gl-skeleton)
set(PROJECT_NAME gl-skeleton)
set(LIB_DIR lib)

set(CMAKE_CXX_STANDARD 14)
file(GLOB_RECURSE SRC_FILES src/utils/*.cpp src/utils/*.h src/*.cpp src/*.h src/*.hpp src/app/*.cpp src/app/*.h)
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES} src/app/texture/Texture.cpp src/app/texture/Texture.h)

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

# SOIL
find_library(SOIL soil HINTS ${LIB_DIR}/lib/SOIL)

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)

target_link_libraries(
        ${PROJECT_NAME}
        glfw
        ${SOIL}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${EXTRA_LIBS}
)
