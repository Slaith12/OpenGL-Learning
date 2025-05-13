#include "Input.hpp"
#include "Engine.hpp"

#define NUM_KEYS (GLFW_KEY_LAST + 1)

namespace Input
{
    /// <summary>
    /// Ring buffer containing all key states from current polling interval and previous two intervals
    /// Key states from previous intervals are used for input state.
    /// </summary>
    char keyStateBuffer[NUM_KEYS * 3];
    int bufferFront;

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {

    }

    void Init(GLFWwindow* window)
    {
        glfwSetKeyCallback(window, key_callback);
        bufferFront = 0;
    }

    void Update(GLFWwindow* window)
    {
        //shift buffer
        bufferFront++;
        if (bufferFront >= 3)
            bufferFront = 0;
        //clear new front buffer
        int bufferMid = bufferFront - 1;
        if (bufferMid == -1)
            bufferMid = 2;
        int frontOffset = bufferFront * NUM_KEYS;
        int midOffset = bufferMid * NUM_KEYS;
        for (int i = 0; i < NUM_KEYS; i++)
        {
            keyStateBuffer[frontOffset + i] = keyStateBuffer[midOffset + i];
        }
    }
}