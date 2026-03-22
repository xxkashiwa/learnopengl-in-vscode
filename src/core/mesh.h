#pragma once

#include <glad/glad.h>

// 顶点结构体：位置、法线、颜色、UV
struct Vertex
{
    float position[3];
    float normal[3];
    float color[3];
    float texCoord[2];
};

struct SimpleVertex
{
    float position[3];
    float texCoord[2];
};

// 一个简单的网格封装 VAO/VBO/EBO
struct Mesh
{
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    GLsizei indexCount = 0;
};

// 创建一个屏幕中心的矩形（两个三角形）
Mesh createQuadMesh();
Mesh createSimpleCube();

// 释放 Mesh 对应的 OpenGL 资源
void destroyMesh(Mesh &mesh);
