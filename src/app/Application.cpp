#include "Application.h"
GLfloat mix;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        std::cout << "uppding to " << mix << std::endl;
        if (mix < 1.0f) mix = mix + 0.1f;
        return;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        std::cout << "downning to " << mix << std::endl;
        if (mix > 0) mix = mix - 0.1f;
        return;
    }
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}


Application::Application(int &height, int &width, std::string name)
    : name(std::move(name)), height(height), width(width)
{
    this->running = false;
    this->initialized = false;
    glfwInit();
    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glewExperimental = GL_TRUE;

    this->window = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);

    glViewport(0, 0, this->width, this->height);
    int screenWidth, screenHeight;

    glfwGetFramebufferSize(this->window, &screenWidth, &screenHeight);
    glfwMakeContextCurrent(this->window);
    const int glew_init_ret_code = glewInit();

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(this->window, true);


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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

Application::~Application() {
    ImGui_ImplGlfwGL3_Shutdown();
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
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left
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

    std::string wall_fn = "assets/textures/wall.jpg";
    std::string af_fn = "assets/textures/awesomeface.png";
    Texture texture1(wall_fn, TextureColorModel::RGB);
    Texture texture2(af_fn, TextureColorModel::RGBA);

    p.use();
    glUniform1i(p.get_uniform_location("Texture"), 0);
    glUniform1i(p.get_uniform_location("Texture2"), 1);
    glUniform1f(p.get_uniform_location("u_mix"), mix);
    glfwSetKeyCallback(this->window, key_callback);

    while (!glfwWindowShouldClose(this->window)) {
        ImGui_ImplGlfwGL3_NewFrame();
        {
            ImGui::Begin("Debug info:");
            static float f = 0.0f;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        glUniform1f(p.get_uniform_location("u_mix"), mix);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
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
