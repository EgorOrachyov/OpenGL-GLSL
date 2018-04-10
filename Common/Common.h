//
// Created by Egor Orachyov on 10.04.2018.
//

#ifndef OPENGL_GLSL_COMMON_H
#define OPENGL_GLSL_COMMON_H

//--------------------------------------------------------------
// Compilation mode
//--------------------------------------------------------------

#define DEBUG

//--------------------------------------------------------------
// Standard includes
//--------------------------------------------------------------

#include <ctime>
#include <cstdio>
#include <cwchar>
#include <cstdlib>
#include <cstring>

//--------------------------------------------------------------
// OpenGL includes
//--------------------------------------------------------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//--------------------------------------------------------------
// Common consts
//--------------------------------------------------------------

const int STRING_SIZE = 512;
const int BUFFER_SIZE = 16000;

//--------------------------------------------------------------
// Debug tools
//--------------------------------------------------------------

#ifdef DEBUG
    #define ASSERT(condition) { \
        if (condition) { \
            \
        } else { \
            fprintf(stderr, "[ASSERT:ERROR] CONDITION: %s, LINE: %i, FILE: %s \n", #condition, __LINE__, __FILE__); \
        } \
    }
#else
    #define ASSERT(condition)
#endif

#ifdef DEBUG
    #define INFO(message) { \
        fprintf(stdout, "[INFO]: %s, LINE: %i, FILE: %s \n", message, __LINE__, __FILE__); \
    }
#else
    #define INFO(message)
#endif

#ifdef DEBUG
    #define WARNING(message) { \
        fprintf(stdout, "[WARNING]: %s, LINE: %i, FILE: %s \n", message, __LINE__, __FILE__); \
    }
#else
    #define WARNING(message)
#endif

#ifdef DEBUG
    #define ERROR(message) { \
        fprintf(stderr, "[ERROR]: %s, LINE: %i, FILE: %s \n", message, __LINE__, __FILE__); \
    }

    #define ERROR_LOG(message, log) { \
        fprintf(stderr, "[ERROR]: %s \n%s\nLINE: %i, FILE: %s \n", message, log, __LINE__, __FILE__); \
    }
#else
    #define ERROR(message)
#endif

#endif //OPENGL_GLSL_COMMON_H
