#pragma once

#include <string>
#include "Engine.hpp"

GLObject CompileShader(const char* code, GLenum type);
GLObject LinkShaders(GLObject vertexShader, GLObject fragmentShader);
GLObject CreateShader(const char* vertexPath, const char* fragmentPath);