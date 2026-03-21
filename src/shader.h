#pragma once

#include <string>

#include <glad/glad.h>

class Shader
{
public:
    // 从顶点着色器和片段着色器源码文件路径创建着色器程序
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    // 使用此着色器程序
    void use() const;

    // 获取底层 program id
    unsigned int id() const { return program_; }

    // 常用 uniform 设置接口
    void setBool(const char *name, bool value) const;
    void setInt(const char *name, int value) const;
    void setFloat(const char *name, float value) const;

private:
    unsigned int program_ = 0;

    static std::string loadFile(const char *path);
    static unsigned int compile(unsigned int type, const std::string &source);
};
