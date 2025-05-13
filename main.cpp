#include "Engine.hpp"
#include "Shader.hpp"
#include <iostream>
#include <string>

bool CompileShaders();
void LoadVertices();

void ResizeFrameBuffer(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
void RenderFrame(GLFWwindow* window);
void SetBackColor(float r, float g, float b);
void PrintLine(const std::string& s);

GLObject shaderPrograms[2];
GLObject VAO1, VBO1, EBO1, VAO2, VBO2, EBO2;

int main()
{
    //Initialize GLFW (the library which gives us a window)
    glfwInit();
    //Tell GLFW to use OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        PrintLine("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, ResizeFrameBuffer);

    //Initialize GLAD (handles OpenGL driver functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PrintLine("Failed to initialize GLAD");
        glfwTerminate();
        return -1;
    }

    if (!CompileShaders())
    {
        glfwTerminate();
        return -1;
    }
    LoadVertices();

    SetBackColor(0.2f, 0.3f, 0.3f);
    
    Input::Init(window);

    while (!glfwWindowShouldClose(window))
    {
        Input::Update(window);
        ProcessInput(window);
        RenderFrame(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

bool CompileShaders()
{
    shaderPrograms[0] = CreateShader("vertexShader.glsl", "fragmentShader.glsl");
    shaderPrograms[1] = CreateShader("vertexShader.glsl", "fragmentShader2.glsl");
    return true;
}

void LoadVertices()
{
    float vertices1[] = {
     0.4f,  0.7f,  0.0f,  // T1 Top
     0.2f,  0.2f,  0.0f,  // T1 Left
     0.6f,  0.2f,  0.0f,  // T1 Right
     //0.6f, -0.1f,  0.0f,
    };
    float vertices2[] = {
     0.0f,  -0.2f, 0.0f,  // T2 Top
     -0.2f, -0.7f, 0.0f,  // T2 Left
     0.2f,  -0.7f, 0.0f,  // T2 Right
     //-0.4f, -0.9f,  0.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
    };

    //Create VAO which will store attribute settings, and bind it.
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    //Create the buffers to hold vertex data, then bind and populate them.
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    //Copy the vertex data to the buffer
    //GL_STATIC_DRAW means the data's only set once and used many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Tell OpenGL how to interpret the vertex data
    //This says where to find the aPos data (set to location 0 in our shader code) and the size/spacing of the data
    //It will look for this data at the currently bound VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &EBO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void ResizeFrameBuffer(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        SetBackColor(0.9f, 0.2f, 0.6f);
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        SetBackColor(0.2f, 0.3f, 0.3f);
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        SetBackColor(0.6f, 0.8f, 0.1f);
    }
}

void RenderFrame(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(shaderPrograms[0]);
    //since we only have one each of these, we don't need to rebind it every single update, but it could be necessary when using different VAOs
    glBindVertexArray(VAO1);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
    glUseProgram(shaderPrograms[1]);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

}

void SetBackColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
}

void PrintLine(const std::string& s)
{
    std::cout << s << std::endl;
}
