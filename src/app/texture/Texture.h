#pragma once
#ifndef GL_SKELETON_TEXTURE_H
#define GL_SKELETON_TEXTURE_H
#include <iostream>
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../../utils/file.h"

enum TextureColorModel {
    RGBA = GL_RGBA,
    RGB = GL_RGB,
    BGR = GL_BGR
};

class Texture {
public:
    explicit Texture(std::string& file_name, TextureColorModel);
    explicit Texture(const char* file_name, TextureColorModel);
    void load_new_image(std::string& file_name, TextureColorModel);
    void bind();
    ~Texture();


    GLuint id;
    TextureColorModel color_model;
};


#endif
