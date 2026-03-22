#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode = loadFile(vertexPath);
    std::string fragmentCode = loadFile(fragmentPath);

    unsigned int vertexShader = compile(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentCode);

    program_ = glCreateProgram();
    glAttachShader(program_, vertexShader);
    glAttachShader(program_, fragmentShader);
    glLinkProgram(program_);

    int success = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program_, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    if (program_ != 0)
    {
        glDeleteProgram(program_);
    }
}

void Shader::use() const
{
    glUseProgram(program_);
}

void Shader::setBool(const char *name, bool value) const
{
    int location = glGetUniformLocation(program_, name);
    glUniform1i(location, value ? 1 : 0);
}

void Shader::setInt(const char *name, int value) const
{
    int location = glGetUniformLocation(program_, name);
    glUniform1i(location, value);
}

void Shader::setFloat(const char *name, float value) const
{
    int location = glGetUniformLocation(program_, name);
    glUniform1f(location, value);
}
void Shader::setMat4(const char *name, glm::mat4 value) const
{
    int location = glGetUniformLocation(program_, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
std::string Shader::loadFile(const char *path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << path << std::endl;
        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::compile(unsigned int type, const std::string &source)
{
    unsigned int shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    return shader;
}
