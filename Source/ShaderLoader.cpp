//
// Created by Egor Orachyov on 10.04.2018.
//

#include "../Common/ShaderLoader.h"

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


    char buffer[BUFFER_SIZE];
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
            char log[logLen];

            GLsizei written;
            glGetShaderInfoLog(shader, logLen, &written, log);

            ERROR_LOG("Shader log:",log);
        }
    }

    return  NULL;
}