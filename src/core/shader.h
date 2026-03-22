#pragma once

#include <glad/glad.h>

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    void use() const;

    void setBool(const char *name, bool value) const;
    void setInt(const char *name, int value) const;
    void setFloat(const char *name, float value) const;
    void setMat4(const char *name, glm::mat4 value) const;

private:
    std::string loadFile(const char *path);
    unsigned int compile(unsigned int type, const std::string &source);

    unsigned int program_ = 0;
};
