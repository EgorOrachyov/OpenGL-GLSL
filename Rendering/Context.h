//
// Created by Egor Orachyov on 10.04.2018.
//

#ifndef OPENGL_GLSL_CONTEXT_H
#define OPENGL_GLSL_CONTEXT_H

#include "OpenGL-GLSL/Common/Common.h"
#include "OpenGL-GLSL/Rendering/Rendering.h"

void PrintContextInfo();

void InitContext();

void DestroyContext();

GLFWwindow * GetCurrentContext();

void APIENTRY debugCallback( GLenum source, GLenum type, GLuint id,
                             GLenum severity, GLsizei length, const GLchar * msg, const void * param );

#endif //OPENGL_GLSL_CONTEXT_H
