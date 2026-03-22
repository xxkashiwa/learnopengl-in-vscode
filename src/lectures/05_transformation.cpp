#include "stb_image.h" //图像加载库
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "../core/mesh.h"
#include "../core/window.h"
#include "../core/shader.h"
#include "../core/imgui_layer.h"

void do_transformation(Shader &shader, const glm::vec3 &translation, float rotation_deg, const glm::vec3 &scale)
{
    glm::mat4 trans = glm::mat4(1.0f); // 4x4 identity matrix
    trans = glm::translate(trans, translation);
    trans = glm::rotate(trans, glm::radians(rotation_deg), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, scale);
    shader.setMat4("transform", trans);
}
void texture_04(GLuint &texture0, GLuint &texture1);
int main05()
{
    GLFWwindow *window = initWindow(800, 600, "LearnOpenGL");
    if (!window)
    {
        return -1;
    }
    Gui::Init(window);

    GLuint texture0;
    GLuint texture1;
    texture_04(texture0, texture1);
    Mesh quad = createQuadMesh();
    Shader shader("shaders/05_vertex_shader.glsl", "shaders/05_fragment_shader.glsl");
    shader.use();
    shader.setInt("texture0", 0); // 指定对应uniform变量使用的纹理单元
    shader.setInt("texture1", 1);

    glm::vec3 translation(0.5f, -0.5f, 0.0f);
    float rotation_deg = 0.0f;
    glm::vec3 scale(1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        Gui::BeginFrame();

        ImGui::Begin("Transform Controls");
        ImGui::SliderFloat3("Translate", glm::value_ptr(translation), -1.0f, 1.0f);
        ImGui::SliderFloat("Rotate Z (deg)", &rotation_deg, 0.0f, 360.0f);
        ImGui::SliderFloat3("Scale", glm::value_ptr(scale), 0.1f, 3.0f);
        ImGui::End();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        do_transformation(shader, translation, rotation_deg, scale);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glBindVertexArray(quad.vao);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode 线框模式
        glDrawElements(GL_TRIANGLES, quad.indexCount, GL_UNSIGNED_INT, 0);

        glfwPollEvents();

        // Rendering GUI
        Gui::EndFrame();
        glfwSwapBuffers(window);
    }

    Gui::Shutdown();
    destroyMesh(quad);
    glfwTerminate();
    return 0;
}

void texture_04(GLuint &texture0, GLuint &texture1)
{
    glGenTextures(1, &texture0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *data0 = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data0)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data0);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data0);

    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data1 = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data1);
}
