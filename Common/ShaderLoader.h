//
// Created by Egor Orachyov on 10.04.2018.
//

#ifndef OPENGL_GLSL_SHADERLOADER_H
#define OPENGL_GLSL_SHADERLOADER_H

#include "Common.h"

char * LoadShaderAsString(char * shaderName);

GLuint LoadShaderObject(GLenum shaderType, char * shaderText);

#endif //OPENGL_GLSL_SHADERLOADER_H
