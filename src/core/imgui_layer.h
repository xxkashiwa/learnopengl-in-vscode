#pragma once

#include <GLFW/glfw3.h>

namespace Gui
{
    // Initialize Dear ImGui context and backends for a given GLFW window
    void Init(GLFWwindow *window);

    // Start a new ImGui frame (call once per frame before building any GUI)
    void BeginFrame();

    // Render the current ImGui draw data to the current framebuffer
    void EndFrame();

    // Shutdown Dear ImGui and backends
    void Shutdown();
}
