#pragma once

#include <GLFW/glfw3.h>

// 创建并初始化一个 OpenGL 窗口，失败返回 nullptr
GLFWwindow *initWindow(int width, int height, const char *title);

// 帧缓冲大小变化回调（由 initWindow 内部注册）
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// 统一的输入处理：Esc 关闭窗口
void processInput(GLFWwindow *window);
