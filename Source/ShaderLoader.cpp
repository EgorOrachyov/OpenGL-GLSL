//
// Created by Egor Orachyov on 10.04.2018.
//

#include "../Common/ShaderLoader.h"

char * LoadShaderAsString(char * shaderName)
{
    if (!shaderName) {
        WARNING("NULL shader name string");
        return NULL;
    }

    FILE * file = fopen(shaderName, "r");
    if (!file) {
        WARNING("Cannot open file");
        return NULL;
    }


    char buffer[BUFFER_SIZE];
    int readChars = 0;
    while (!feof(file)) {
        char c = fgetc(file);
        buffer[readChars] = c;
        readChars += 1;
    }
    readChars -= 1;
    buffer[readChars] = '\0';
    readChars += 1;

    char * shaderCode = (char *)calloc(readChars, sizeof(char));
    if (!shaderCode) {
        WARNING("Cannot allocate memory");
        return NULL;
    }

    memcpy(shaderCode, buffer, readChars * sizeof(char));

    return  shaderCode;
}

GLuint LoadShaderObject(GLenum shaderType, char * shaderText)
{

}