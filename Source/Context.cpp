//
// Created by Egor Orachyov on 10.04.2018.
//

#include <string>
#include "OpenGL-GLSL/Rendering/Context.h"

static GLFWwindow * m_window;

void APIENTRY debugCallback( GLenum source, GLenum type, GLuint id,
                             GLenum severity, GLsizei length, const GLchar * msg, const void * param ) {

    using std::string;

    string sourceStr;
    switch(source) {
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceStr = "WindowSys";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            sourceStr = "App";
            break;
        case GL_DEBUG_SOURCE_API:
            sourceStr = "OpenGL";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceStr = "ShaderCompiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceStr = "3rdParty";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            sourceStr = "Other";
            break;
        default:
            sourceStr = "Unknown";
    }

    string typeStr;
    switch(type) {
        case GL_DEBUG_TYPE_ERROR:
            typeStr = "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeStr = "Deprecated";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeStr = "Undefined";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            typeStr = "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeStr = "Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            typeStr = "Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeStr = "PushGrp";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            typeStr = "PopGrp";
            break;
        case GL_DEBUG_TYPE_OTHER:
            typeStr = "Other";
            break;
        default:
            typeStr = "Unknown";
    }

    string sevStr;
    switch(severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            sevStr = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            sevStr = "MED";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            sevStr = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            sevStr = "NOTIFY";
            break;
        default:
            sevStr = "UNK";
    }

    printf("%s:%s[%s](%d): %s\n", sourceStr.c_str(), typeStr.c_str(), sevStr.c_str(),
           id, msg);
}

void PrintContextInfo()
{
    const GLubyte * renderer = glGetString(GL_RENDERER);
    const GLubyte * vendor = glGetString(GL_VENDOR);
    const GLubyte * version = glGetString(GL_VERSION);
    const GLubyte * glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint minor, major;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor            : %s\n", vendor);
    printf("GL Renderer          : %s\n", renderer);
    printf("GL Version (string)  : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version         : %s\n", glslVersion);

    GLint numOfExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numOfExtensions);

    printf("\nGL Extensions:\n");
    for(int i = 0; i < numOfExtensions; i++)
        printf("%s\n", glGetStringi(GL_EXTENSIONS, i));

    printf("\n\n");
}

void InitContext()
{
    int isInitialized = glfwInit();
    ASSERT(isInitialized, "Cannot initialize glfw");

#ifdef __APPLE__
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

    m_window = glfwCreateWindow( 640, 480, "Hello World", NULL, NULL );
    if (!m_window)
    {
        glfwTerminate();
        ASSERT(m_window, "Cannot create glfw window");
    }

    glfwMakeContextCurrent(m_window);
    glewInit();

    //glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(debugCallback, NULL);
    //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
}

void DestroyContext()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

GLFWwindow * GetCurrentContext()
{
    return m_window;
}