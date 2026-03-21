#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "window.h"
#include "mesh.h"

GLuint shaderProgram;
GLuint vertexShader;
GLuint fragmentShader;
void shader_local()
{

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
}

int main03()
{
    GLFWwindow *window = initWindow(800, 600, "LearnOpenGL");
    if (!window)
    {
        return -1;
    }

    Mesh quad = createQuadMesh();
    shader_local();
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + .5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(quad.vao);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode 线框模式
        glDrawElements(GL_TRIANGLES, quad.indexCount, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    destroyMesh(quad);
    glfwTerminate();
    return 0;
}
