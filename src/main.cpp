#include <iostream>
#include "app/Application.h"
#include "app/shader/Shader.h"
#include "app/texture/Texture.h"

#define FRAME_LIMIT 30

int main() {
    std::string name = "GL playground";
    int width = 800, height = 600;
    Application a(height, width, name, FRAME_LIMIT);
    a.loop();
    return 0;
}