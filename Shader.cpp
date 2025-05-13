#include "Shader.hpp"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

GLObject CompileShader(const char* code, GLenum type)
{
    int success;
    char infoLog[512];

    GLObject shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        glDeleteShader(shader);
        throw std::exception(("Shader compilation failed.\n" + std::string(infoLog)).c_str());
    }
    return shader;
}

GLObject LinkShaders(GLObject vertexShader, GLObject fragmentShader)
{
    int success;
    char infoLog[512];

    GLObject program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        glDeleteProgram(program);
        throw std::exception(("Shader program linking failed.\n" + std::string(infoLog)).c_str());
    }

    return program;
}

GLObject CreateShader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        throw std::exception("Unable to read shader files.");
    }

    GLObject vertexShader = CompileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
    GLObject fragmentShader = CompileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);
    GLObject program = LinkShaders(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
