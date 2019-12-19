//
// Created by Egor Orachyov on 10.04.2018.
//

#ifndef OPENGL_GLSL_SHADERLOADER_H
#define OPENGL_GLSL_SHADERLOADER_H

#include "Common.h"
#include "../Rendering/Rendering.h"

char * LoadShaderAsString(char * shaderName);

GLuint LoadShaderObject(GLenum shaderType, char * shaderText);

GLuint LoadShaderProgram(GLuint * shaders, GLuint size);

void UseShaderProgram(GLuint programHandle);

void BindAttributeLocation(GLuint handle, GLuint location, char * attributeName);

void BindFragmentLocation(GLuint handle, GLuint location, char * attributeName);

void PrintActiveUniforms(GLuint handle);

void PrintActiveAttributes(GLuint handle);

const char * GetTypeString(GLenum type);

#endif //OPENGL_GLSL_SHADERLOADER_H
