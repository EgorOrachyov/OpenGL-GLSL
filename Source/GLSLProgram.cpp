//
// Created by Egor Orachyov on 01.05.2018.
//

#include "OpenGL-GLSL/Rendering/GLSLProgram.h"

GLSLProgram::GLSLProgram()
{

}

GLSLProgram::~GLSLProgram()
{

}


void GLSLProgram::init()
{

}

void GLSLProgram::destroy()
{

}


void GLSLProgram::compileShader(const char * shader, GLSLShaderType type)
{

}


void GLSLProgram::link()
{

}

void GLSLProgram::use()
{

}

void GLSLProgram::bindAttribLocation(GLuint location, const char * name)
{

}

void GLSLProgram::bindFragDataLocation(GLuint location, const char * name)
{

}

void GLSLProgram::printActiveUniforms()
{

}

void GLSLProgram::printActiveUniformBlocks()
{

}

void GLSLProgram::printActiveAttribs()
{
#ifdef __APPLE__
    // For OpenGL 4.1, use glGetActiveAttrib
    GLint written, size, location, maxLength, nAttribs;
    GLenum type;
    GLchar * name;

    glGetProgramiv(m_programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
    glGetProgramiv(m_programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);

    name = new GLchar[maxLength];
    printf("Active Attributes: \n");
    printf("------------------------------------------------\n");
    for( int i = 0; i < nAttribs; i++ ) {
        glGetActiveAttrib( m_programHandle, i, maxLength, &written, &size, &type, name );
        location = glGetAttribLocation(m_programHandle, name);
        printf(" %-5d %s (%s)\n", location, name, getTypeString(type));
    }
    delete [] name;
#else
    // >= OpenGL 4.3, use glGetProgramResource
  GLint numAttribs;
  glGetProgramInterfaceiv( m_programHandle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttribs);

  GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

  printf("Active attributes:\n");
  for( int i = 0; i < numAttribs; ++i ) {
    GLint results[3];
    glGetProgramResourceiv(m_programHandle, GL_PROGRAM_INPUT, i, 3, properties, 3, NULL, results);

    GLint nameBufSize = results[0] + 1;
    char * name = new char[nameBufSize];
    glGetProgramResourceName(m_programHandle, GL_PROGRAM_INPUT, i, nameBufSize, NULL, name);
    printf("%-5d %s (%s)\n", results[2], name, getTypeString(results[1]));
    delete [] name;
  }
#endif
}

const char * GLSLProgram::getTypeString( GLenum type )
{
    switch(type) {
        case GL_FLOAT:
            return "float";
        case GL_FLOAT_VEC2:
            return "vec2";
        case GL_FLOAT_VEC3:
            return "vec3";
        case GL_FLOAT_VEC4:
            return "vec4";
        case GL_DOUBLE:
            return "double";
        case GL_INT:
            return "int";
        case GL_UNSIGNED_INT:
            return "unsigned int";
        case GL_BOOL:
            return "bool";
        case GL_FLOAT_MAT2:
            return "mat2";
        case GL_FLOAT_MAT3:
            return "mat3";
        case GL_FLOAT_MAT4:
            return "mat4";
        default:
            return "?";
    }
}
