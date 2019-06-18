#ifndef GL_SKELETON_SHADER_H
#define GL_SKELETON_SHADER_H
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <string>
#include "../../utils/file.h"

enum ShaderType {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
};


class Shader {
public:
    explicit Shader(const char* code, ShaderType type);
    explicit Shader(std::string& shader_file_name, ShaderType type);
    ~Shader();



    GLuint id;
    GLuint* program_id;
    ShaderType type;
};


#endif
