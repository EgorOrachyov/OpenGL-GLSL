//
// Created by Egor Orachyov on 01.05.2018.
//

#ifndef OPENGL_GLSL_GLSLPROGRAM_H
#define OPENGL_GLSL_GLSLPROGRAM_H

#include "OpenGL-GLSL/Common/Common.h"
#include "OpenGL-GLSL/Rendering/Rendering.h"

class GLSLProgram
{
private:

    GLuint m_programHandle;
    GLuint m_isLinked;

public:
    GLSLProgram();
    ~GLSLProgram();

    void init();
    void destroy();

    void compileShader(const char * shader, GLSLShaderType type);

    void link();
    void use();

    void   bindAttribLocation(GLuint location, const char * name);
    void   bindFragDataLocation(GLuint location, const char * name);

    void   printActiveUniforms();
    void   printActiveUniformBlocks();
    void   printActiveAttribs();

    const char * getTypeString(GLenum type);
};

#endif //OPENGL_GLSL_GLSLPROGRAM_H
