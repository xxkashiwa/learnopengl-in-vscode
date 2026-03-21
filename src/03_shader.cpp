#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "./02_vbo_vao_ebo.cpp"
int main03()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD \n";
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    vbo_vao_ebo();

    // start here
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    shaderProgram = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 2) in vec3 aColor;

    out vec4 vOutColor;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        vOutColor = vec4(aColor,1.0);
    }
    )";
    const char *fragmentShaderSource = R"(
    #version 330 core
    in vec4 vOutColor;

    out vec4 FragColor;

    uniform float ourColor;
    void main()
    {   
        // FragColor = ourColor; 
        FragColor = vOutColor;
    } 
    )";

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + .5f;
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); // 这里更新了uniform，但我们未在shader中使用它，要使用则需要在fragmentShader启用Frag = ourColor

        glBindVertexArray(vao);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode 线框模式
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // --- 释放 OpenGL 资源 ---
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();
    return 0;
}