#include "stb_image.h" //图像加载库
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../core/mesh.h"
#include "../core/window.h"
#include "../core/shader.h"

float yaw, pitch;
float lastX = 400, lastY = 300;
bool firstMouse = true;
float fov = 45.0f;

void MVP(Shader &shader, glm::vec3 &translation, float rotation_deg, glm::vec3 &scale, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(model, scale);
    model = glm::translate(model, translation);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f) + rotation_deg, glm::vec3(1.0f, 0.0f, 1.0f)); // 时间旋转+输入的主动旋转

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
    shader.setMat4("modelTransform", model);
    shader.setMat4("viewTransform", view);
    shader.setMat4("projectionTransform", projection);
}

void processCameraLookArount(glm::vec3 &cameraFront);
void processCameraMove(GLFWwindow *window, glm::vec3 &cameraPos, const glm::vec3 &cameraFront, glm::vec3 &cameraUp, float deltaTime);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void texture_06(GLuint &texture0, GLuint &texture1);

int main06()
{
    GLFWwindow *window = initWindow(800, 600, "LearnOpenGL");
    if (!window)
    {
        return -1;
    }

    GLuint texture0;
    GLuint texture1;
    texture_06(texture0, texture1);
    Mesh cube = createSimpleCube();
    Shader shader("shaders/06_vertex_shader.glsl", "shaders/06_fragment_shader.glsl");
    shader.use();
    shader.setInt("texture0", 0); // 指定对应uniform变量使用的纹理单元
    shader.setInt("texture1", 1);

    glm::vec3 translation(0.0f, 0.0f, 0.0f);
    float rotation_deg = 0.0f;
    glm::vec3 scale(1.0f, 1.0f, 1.0f);

    // camera
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        processCameraLookArount(cameraFront);
        processCameraMove(window, cameraPos, cameraFront, cameraUp, deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glBindVertexArray(cube.vao);
        MVP(shader, translation, rotation_deg, scale, cameraPos, cameraFront, cameraUp);
        glDrawElements(GL_TRIANGLES, cube.indexCount, GL_UNSIGNED_INT, 0);
        auto trans1 = translation + glm::vec3(1.0f, 1.0f, 1.0f);
        MVP(shader, trans1, rotation_deg, scale, cameraPos, cameraFront, cameraUp);
        glDrawElements(GL_TRIANGLES, cube.indexCount, GL_UNSIGNED_INT, 0);
        auto trans2 = translation + glm::vec3(2.0f, 1.0f, 2.0f);
        MVP(shader, trans2, rotation_deg, scale, cameraPos, cameraFront, cameraUp);
        glDrawElements(GL_TRIANGLES, cube.indexCount, GL_UNSIGNED_INT, 0);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    destroyMesh(cube);
    glfwTerminate();
    return 0;
}
void processCameraLookArount(glm::vec3 &cameraFront)
{
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);
}
void processCameraMove(GLFWwindow *window, glm::vec3 &cameraPos, const glm::vec3 &cameraFront, glm::vec3 &cameraUp, float deltaTime)
{

    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 75.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 75.0f)
        fov = 75.0f;
}
void texture_06(GLuint &texture0, GLuint &texture1)
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
