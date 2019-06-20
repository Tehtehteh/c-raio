#ifndef GL_SKELETON_APPLICATION_H
#define GL_SKELETON_APPLICATION_H
#include <cmath>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include "./shader/Shader.h"
#include "./shader/ShaderProgram.h"
#include "./texture/Texture.h"

class Application {
public:
    Application(int &height, int &width, std::string name);
    ~Application();
    void loop();
protected:
    int height;
    int width;
    GLFWwindow *window;
    std::string name;
    bool running;
    bool initialized;
};


#endif
