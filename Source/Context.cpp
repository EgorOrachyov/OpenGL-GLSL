//
// Created by Egor Orachyov on 10.04.2018.
//

#include "../Common/Context.h"

void PrintContextInfo()
{
    // Print info about renderer and OpenGL
    const GLubyte * renderer = glGetString(GL_RENDERER);
    const GLubyte * vendor = glGetString(GL_VENDOR);
    const GLubyte * version = glGetString(GL_VERSION);
    const GLubyte * glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    const GLubyte * extensions = glGetString(GL_EXTENSIONS);

    printf("GL Vendor    : %s\n", vendor);
    printf("GL Renderer  : %s\n", renderer);
    printf("GL Version   : %s\n", version);
    printf("GLSL Version : %s\n", glslVersion);
    printf("GL Extensions: %s\n", extensions);

    printf("\n");
}

void DestroyContext(GLFWwindow * window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
    INFO("INFO: GLFW has been de-initialized");
}