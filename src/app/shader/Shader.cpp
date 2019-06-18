#include "Shader.h"
#include <iostream>

Shader::Shader(const char *code, ShaderType type) {
    this->type = type;
    this->program_id = nullptr;
    GLuint shader_id;
    shader_id = glCreateShader(this->type);
    glShaderSource(shader_id, 1, &code, nullptr);
    glCompileShader(shader_id);
    this->id = shader_id;
}

Shader::Shader(std::string &shader_file_name, ShaderType type) {
    this->type = type;
    this->program_id = nullptr;
    if(!file_utils::exists(shader_file_name)) return;
    std::string code = file_utils::raw_read(shader_file_name);
    if (code.empty()) {
        return;
    }
    GLuint shader_id;
    shader_id = glCreateShader(this->type);
    const char* pCode = code.c_str();
    glShaderSource(shader_id, 1, &pCode, nullptr);
    glCompileShader(shader_id);
    this->id = shader_id;
    int success;
    char infoLog[1024];
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(this->id, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(this->id);
}

