//
// Created by Egor Orachyov on 10.04.2018.
//

#include "Common/Common.h"
#include "Common/Context.h"
#include "Common/ShaderLoader.h"

int main()
{
    GLFWwindow * window = NULL;
    char name[] = "OpenGL-GLSL";

    glfwInit();
    window = glfwCreateWindow(1000, 600, name, NULL, NULL);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwMakeContextCurrent(window);
    glewInit();
    PrintContextInfo();

    char vertShader[] = "../Shaders/basic.vert";
    char * shaderCode = LoadShaderAsString(vertShader);
    GLuint vsID = LoadShaderObject(GL_VERTEX_SHADER, shaderCode);

    bool isDone = false;
    while(!isDone)
    {
        isDone = (bool)glfwWindowShouldClose(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    INFO("Close GLFW window");


    return 0;
}
