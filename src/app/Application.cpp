#include "Application.h"


Application::Application(int &height, int &width, std::string name)
    : name(std::move(name)), height(height), width(width)
{
    this->running = false;
    this->initialized = false;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glewExperimental = GL_TRUE;

    this->window = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);
    glViewport(0, 0, this->width, this->height);
    int screenWidth, screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glfwMakeContextCurrent(window);
    const int glew_init_ret_code = glewInit();
    if (glew_init_ret_code != 0) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return;
    }
    glewExperimental = GL_TRUE;

    if (window == nullptr) {
        std::cout << "Failed to initialize window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}

Application::~Application() {
    glfwTerminate();
}

void Application::loop() {
    this->running = true;
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    std::string vpath = "assets/shaders/vshader.glsl";
    std::string fpath = "assets/shaders/fshader.glsl";
    Shader vshader(vpath, ShaderType::VERTEX);
    Shader fshader(fpath, ShaderType::FRAGMENT);
    ShaderProgram p (std::vector<Shader>{vshader, fshader});
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Texture texture1("assets/textures/wall.jpg");
    Texture texture2("assets/textures/awesomeface.png");
    texture2.bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    p.use();
    glUniform1i(glGetUniformLocation(p.id, "Texture"), 0); // set it manually
    glUniform1i(glGetUniformLocation(p.id, "Texture2"), 1); // set it manually


    while (!glfwWindowShouldClose(this->window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        texture1.bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.bind();
        p.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    this->running = false;
}
