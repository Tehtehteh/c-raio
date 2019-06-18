#include "Texture.h"

Texture::~Texture() {
    // Because of *GLuint
    const GLuint buf[1] = {this->id};
    glDeleteTextures(1, buf);
}

Texture::Texture(std::string &file_name) {
    if (file_utils::exists(file_name)) {
        this->id = 0;
        return;
    }
    this->id = SOIL_load_OGL_texture(file_name.c_str(),
            SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (this->id == 0) {
        std::cout << "Failed to load image into OGL texture. Error: " << SOIL_last_result() << std::endl;
    }
}



Texture::Texture(char *file_name) {
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widht, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    this->id = texture_id;
    SOIL_free_image_data(data);
//    this->id = SOIL_load_OGL_texture(file_name,
//            SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
//            SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
//    );
//    if (this->id == 0) {
//        std::cout << "Failed to load image into OGL texture. Error: " << SOIL_last_result() << std::endl;
//    }
}

void Texture::load_new_image(std::string &file_name) {
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widht, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    this->id = texture_id;
    SOIL_free_image_data(data);
//    this->id = SOIL_load_OGL_texture(file_name.c_str(),
//            SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
//            SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
//    );
//    if (this->id == 0) {
//        std::cout << "Failed to load image into OGL texture. Error: " << SOIL_last_result() << std::endl;
//    }

}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
