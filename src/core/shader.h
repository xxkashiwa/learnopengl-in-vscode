#pragma once

#include <glad/glad.h>

#include <string>

class Shader
{
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    void use() const;

    void setBool(const char *name, bool value) const;
    void setInt(const char *name, int value) const;
    void setFloat(const char *name, float value) const;

private:
    std::string loadFile(const char *path);
    unsigned int compile(unsigned int type, const std::string &source);

    unsigned int program_ = 0;
};
