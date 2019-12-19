//
// Created by Egor Orachyov on 01.05.2018.
//

#ifndef OPENGL_GLSL_RENDERING_H
#define OPENGL_GLSL_RENDERING_H

//--------------------------------------------------------------
// OpenGL includes
//--------------------------------------------------------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//--------------------------------------------------------------
// Enums
//--------------------------------------------------------------

enum GLSLShaderType {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    COMPUTE = GL_COMPUTE_SHADER
};

#endif //OPENGL_GLSL_RENDERING_H
