#include "Texture.h"

Texture::~Texture() {
    // Because of *GLuint
    const GLuint buf[1] = {this->id};
    glDeleteTextures(1, buf);
}

Texture::Texture(std::string &file_name, const TextureColorModel cm): Texture(file_name.c_str(), cm) {
}


Texture::Texture(const char *file_name, const TextureColorModel cm) : color_model(cm) {
    std::string f_name = file_name;
    if (!file_utils::exists(f_name)) {
        this->id = 0;
        return;
    }
    int widht, height, channels;
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    unsigned char* data = SOIL_load_image(file_name, &widht, &height, &channels, 0);
    if (data == nullptr) {
        return;
    }
    if (channels == 4 && this->color_model != TextureColorModel::RGBA) {
        std::cout << "Warning: trying to load image into texture in RGB format, while image is RGBA " << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, this->color_model, widht, height, 0, this->color_model, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    this->id = texture_id;
    SOIL_free_image_data(data);
}

void Texture::load_new_image(std::string &file_name, const TextureColorModel cm) {
    if (!file_utils::exists(file_name)) {
        return;
    }
    int widht, height, channels;
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    unsigned char* data = SOIL_load_image(file_name.c_str(), &widht, &height, &channels, 0);
    if (data == nullptr) {
        return;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, cm, widht, height, 0, cm, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    this->id = texture_id;
    this->color_model = cm;
    SOIL_free_image_data(data);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
