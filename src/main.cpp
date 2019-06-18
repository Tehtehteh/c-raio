#include <iostream>
#include "app/Application.h"
#include "app/shader/Shader.h"
#include "app/texture/Texture.h"

int main() {
    std::string name = "GL playground";
    int width = 800, height = 600;
    Application a(height, width, name);
    a.loop();
    return 0;
}