#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef unsigned int GLObject;

namespace Input
{
    /// <summary>
    /// Initializes the input state. Should be called before the update loop starts.
    /// </summary>
    void Init(GLFWwindow* window);

    /// <summary>
    /// Updates the input state. Should be called once at the beginning of every frame.
    /// </summary>
    void Update(GLFWwindow* window);
}