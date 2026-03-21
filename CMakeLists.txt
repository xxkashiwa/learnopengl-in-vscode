cmake_minimum_required(VERSION 3.16)

project(learnopengl_projbook LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 解决 MSVC 对 UTF-8 源码的中文注释发出的 C4819 警告
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 添加 GLFW 源码子目录
add_subdirectory(glfw-3.4)

# 你的可执行程序
add_executable(learnopengl
    src/main.cpp
    src/glad.c
)

# 头文件搜索路径（glad、GLFW、KHR 等）
target_include_directories(learnopengl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.4/include
)

# 链接 GLFW
# glfw-3.4 默认生成的目标名是 glfw（以及别名 glfw::glfw）
target_link_libraries(learnopengl PRIVATE glfw)
