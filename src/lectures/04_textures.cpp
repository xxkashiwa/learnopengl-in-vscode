#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" //图像加载库
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
void texture_local()
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../textures/container.jpg", &width, &height, &nrChannels, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

int main04()
{
    texture_local();
    return 0;
}