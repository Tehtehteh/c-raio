//
// Created by tehtehteh on 2019-06-17.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders) {
    this->shaders = std::move(shaders);
    char buffer[512];
    this->id = glCreateProgram();
    for (Shader& shader : this->shaders) {
        glAttachShader(this->id, shader.id);
    }
    glLinkProgram(this->id);
    int success;
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->id, 512, nullptr, buffer);
        std::cout << "LINKING SHADER ERROR:" << buffer << std::endl;
    }
}

void ShaderProgram::use() {
    glUseProgram(this->id);
}

ShaderProgram::~ShaderProgram() {
    for (Shader& shader: this->shaders) {
        glDeleteShader(shader.id);
    }
    glDeleteProgram(this->id);
}

GLuint ShaderProgram::get_uniform_location(std::string uniform_name) {
    return glGetUniformLocation(this->id, uniform_name.c_str());
}

GLuint ShaderProgram::get_uniform_location(const char *uniform_name) {
    return glGetUniformLocation(this->id, uniform_name);
}

