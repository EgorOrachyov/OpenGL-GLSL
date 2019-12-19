//
// Created by Egor Orachyov on 10.04.2018.
//

#ifndef OPENGL_GLSL_COMMON_H
#define OPENGL_GLSL_COMMON_H

//--------------------------------------------------------------
// Compilation mode
//--------------------------------------------------------------

#define DEBUG 1

//--------------------------------------------------------------
// Standard includes
//--------------------------------------------------------------

#include <ctime>
#include <cstdio>
#include <cwchar>
#include <cstdlib>
#include <cstring>

//--------------------------------------------------------------
// Common consts and buffers
//--------------------------------------------------------------

const int STRING_SIZE_128 = 128;
const int STRING_SIZE_256 = 256;
const int STRING_SIZE_512 = 512;
const int STRING_SIZE_1024 = 512;
const int STRING_SIZE_2048 = 512;

//char STRING_BUFFER_128[128];
//char STRING_BUFFER_256[256];
//char STRING_BUFFER_512[512];
//char STRING_BUFFER_1024[1024];
//char STRING_BUFFER_2048[2048];

//--------------------------------------------------------------
// Debug tools
//--------------------------------------------------------------

#if DEBUG
    #define ASSERT(condition, message) { \
        if (condition) { \
            \
        } else { \
            fprintf(stderr, "[ERROR]: %s\n[CONDITION]: %s, LINE: %i, FILE: %s \n", message, #condition, __LINE__, __FILE__); \
            exit(EXIT_FAILURE); \
        } \
    }

    #define INFO(message) { \
        fprintf(stdout, "[INFO]: %s, LINE: %i, FILE: %s \n", message, __LINE__, __FILE__); \
    }

    #define WARNING(message) { \
        fprintf(stdout, "[WARNING]: %s, LINE: %i, FILE: %s \n", message, __LINE__, __FILE__); \
    }

    #define ERROR(message) { \
        fprintf(stderr, "[ERROR]: %s, LINE: %i, FILE: %s \n", message, __LINE__, __FILE__); \
    }

    #define ERROR_LOG(message, log) { \
        fprintf(stderr, "[ERROR]: %s \n%s\nLINE: %i, FILE: %s \n", message, log, __LINE__, __FILE__); \
    }

#else

    #define ASSERT(condition)

    #define INFO(message)

    #define WARNING(message)

    #define ERROR(message)

#endif

#endif //OPENGL_GLSL_COMMON_H
