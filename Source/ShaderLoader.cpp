//
// Created by Egor Orachyov on 10.04.2018.
//

#include "OpenGL-GLSL/Common/ShaderLoader.h"

char * LoadShaderAsString(char * shaderName)
{
    if (!shaderName)
    {
        ERROR("NULL shader name string");
        exit(EXIT_FAILURE);
    }

    FILE * file = fopen(shaderName, "r");
    if (!file)
    {
        ERROR("Cannot open file");
        exit(EXIT_FAILURE);
    }


    char buffer[STRING_SIZE_2048];
    int readChars = 0;
    while (!feof(file))
    {
        char c = fgetc(file);
        buffer[readChars] = c;
        readChars += 1;
    }
    readChars -= 1;
    buffer[readChars] = '\0';
    readChars += 1;

    char * shaderCode = (char *)calloc(readChars, sizeof(char));
    if (!shaderCode)
    {
        ERROR("Cannot allocate memory");
        exit(EXIT_FAILURE);
    }

    memcpy(shaderCode, buffer, readChars * sizeof(char));

    return  shaderCode;
}

GLuint LoadShaderObject(GLenum shaderType, char * shaderText)
{
    GLuint shader = glCreateShader(shaderType);
    if (!shader)
    {
        ERROR("Cannot create shader");
        exit(EXIT_FAILURE);
    }

    const char * codeArray[] = {shaderText};
    glShaderSource(shader, 1, codeArray, NULL);

    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        ERROR("Shader compilation failed");

        GLint logLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

        if (logLen > 0)
        {
            char log[STRING_SIZE_256];

            GLsizei written;
            glGetShaderInfoLog(shader, logLen, &written, log);

            ERROR_LOG("Shader log:",log);
        }

        exit(EXIT_FAILURE);
    }

    return shader;
}

GLuint LoadShaderProgram(GLuint * shaders, GLuint size)
{
    if (!shaders)
    {
        ERROR("Null shaders' pointer");
        exit(EXIT_FAILURE);
    }

    GLuint programHandle = glCreateProgram();
    if (!programHandle)
    {
        ERROR("Cannot create shader");
        exit(EXIT_FAILURE);
    }

    for(GLuint i = 0; i < size; i++)
        glAttachShader(programHandle, shaders[i]);

    glLinkProgram(programHandle);

    GLint status;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
    if (!status)
    {
        ERROR("Cannot link shader program");

        GLint logLen;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);

        if (logLen > 0)
        {
            char log[STRING_SIZE_512];

            GLsizei written;
            glGetProgramInfoLog(programHandle, logLen, &written, log);

            ERROR_LOG("Shader program log:", log);
        }

        exit(EXIT_FAILURE);
    }

    return programHandle;
}

void UseShaderProgram(GLuint programHandle)
{
    glUseProgram(programHandle);
}

void BindAttributeLocation(GLuint handle, GLuint location, char * attributeName)
{
    glBindAttribLocation(handle, location, attributeName);
}

void BindFragmentLocation(GLuint handle, GLuint location, char * attributeName)
{
    glBindFragDataLocation(handle, location, attributeName);
}

void PrintActiveUniforms(GLuint handle)
{
#ifdef __APPLE__

    GLint numUniforms, size, location, maxLen;
    GLsizei written;
    GLenum type;

    glGetProgramiv( handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
    glGetProgramiv( handle, GL_ACTIVE_UNIFORMS, &numUniforms);

    printf("Active uniforms:\n");
    for(int i = 0; i < numUniforms; i++)
    {
        char name[STRING_SIZE_256];
        glGetActiveUniform( handle, i, maxLen, &written, &size, &type, name );
        location = glGetUniformLocation(handle, name);

        if (location != -1)
            continue;  // Skip uniforms in blocks

        printf(" %-5d %s (%s)\n", location, name, GetTypeString(type));
    }

#else

    GLint numUniforms = 0;
    glGetProgramInterfaceiv(handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

    GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

    printf("Active uniforms:\n");
    for(int i = 0; i < numUniforms; i++)
    {
        GLint results[4];
        glGetProgramResourceiv(handle, GL_UNIFORM, i, 4, properties, 4, NULL, results);

        if (results[3] != -1)
            continue;  // Skip uniforms in blocks

        GLint nameBufSize = results[0] + 1;
        char name[STRING_SIZE_256];
        glGetProgramResourceName(handle, GL_UNIFORM, i, nameBufSize, NULL, name);

        printf("%-5d %s (%s)\n", results[2], name, GetTypeString(results[1]));
    }
#endif
}

void PrintActiveAttributes(GLuint handle)
{
#ifdef __APPLE__

    GLint written, size, location, maxLength, numAttribs;
    GLenum type;

    glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
    glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &numAttribs);

    printf("Active attributes:\n");
    for(int i = 0; i < numAttribs; i++)
    {
        char name[STRING_SIZE_256];
        glGetActiveAttrib( handle, i, maxLength, &written, &size, &type, name );
        location = glGetAttribLocation(handle, name);

        printf(" %-5d %s (%s)\n", location, name, GetTypeString(type));
    }

#else

    GLint numAttributes;
    glGetProgramInterfaceiv(handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttributes);

    GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

    printf("Active attributes:\n");
    for(int i = 0; i < numAttributes; i++)
    {
        GLint results[3];
        glGetProgramResourceiv(handle, GL_PROGRAM_INPUT, i, 3, properties, 3, NULL, results);

        GLint nameBufferSize = results[0] + 1;
        char name[STRING_SIZE_256];
        glGetProgramResourceName(handle, GL_PROGRAM_INPUT, i, nameBufferSize, NULL, name);

        printf("%-5d %s (%s)\n", results[2], name, GetTypeString(results[1]));
    }

#endif
}

const char * GetTypeString(GLenum type)
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