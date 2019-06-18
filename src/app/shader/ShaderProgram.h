#ifndef GL_SKELETON_SHADERPROGRAM_H
#define GL_SKELETON_SHADERPROGRAM_H
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "Shader.h"

class ShaderProgram {

public:
    explicit ShaderProgram(const std::vector<Shader>&);
    ~ShaderProgram();
    void use();
    GLuint get_uniform_location(std::string);
    GLuint get_uniform_location(const char*);
    GLuint id;
    std::vector<Shader> shaders;
};


#endif //GL_SKELETON_SHADERPROGRAM_H
