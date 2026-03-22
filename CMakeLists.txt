cmake_minimum_required(VERSION 3.16)

project(learnopengl_projbook LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

# 解决 MSVC 对 UTF-8 源码的中文注释发出的 C4819 警告
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 添加 GLFW 源码子目录
add_subdirectory(glfw-3.4)

# 收集核心封装和课程示例源码
file(GLOB CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp"
)

file(GLOB THIRDPARTY_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/imgui/*.cpp"
)


file(GLOB LECTURE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lectures/*.cpp"
)

add_executable(learnopengl
    src/main.cpp
    src/glad.c
    ${THIRDPARTY_SOURCES}
    ${CORE_SOURCES}
    ${LECTURE_SOURCES}
)

# 头文件搜索路径（glad、GLFW、KHR 等）
target_include_directories(learnopengl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.4/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core

)

# 链接 GLFW 和 OpenGL
# glfw-3.4 默认生成的目标名是 glfw（以及别名 glfw::glfw）
target_link_libraries(learnopengl PRIVATE glfw OpenGL::GL)
