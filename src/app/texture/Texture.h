#pragma once
#ifndef GL_SKELETON_TEXTURE_H
#define GL_SKELETON_TEXTURE_H
#include <iostream>
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../../utils/file.h"

class Texture {
public:
    explicit Texture(std::string& file_name);
    explicit Texture(char* file_name);
    void load_new_image(std::string& file_name);
    void bind();
    ~Texture();
    GLuint id;

};


#endif
