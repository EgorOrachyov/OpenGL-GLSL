//
// Created by Egor Orachyov on 10.04.2018.
//

#include "Common/Common.h"
#include "Common/ShaderLoader.h"
#include "OpenGL-GLSL/Rendering/Rendering.h"
#include "OpenGL-GLSL/Rendering/Context.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLFWwindow * window;

GLuint BasicTriangle()
{
    char vertPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/basic.vert";
    char fragPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/basic.frag";

    char * vertText = LoadShaderAsString(vertPath);
    char * fragText = LoadShaderAsString(fragPath);

    GLuint vertShader = LoadShaderObject(GL_VERTEX_SHADER, vertText);
    GLuint fragShader = LoadShaderObject(GL_FRAGMENT_SHADER, fragText);

    GLuint num = 2;
    GLuint shaders[] = {vertShader, fragShader};

    GLuint programHandle = LoadShaderProgram(shaders, num);
    UseShaderProgram(programHandle);

    GLuint vaoHandle;

    float positionData[] {
            -0.8, -0.8, 0.0,
            0.8, -0.8, 0.0,
            0.0, 0.8, 0.0
    };
    float colorData[] {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
    };

    // Create and fill buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    // Fill coordinate buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_DYNAMIC_DRAW);

    // Fill color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_DYNAMIC_DRAW);

    // Create vertex array object
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    // Activate arrays of vertex attributes
    glEnableVertexAttribArray(0); //Position
    glEnableVertexAttribArray(1); // Color

    // Fix 0 for position data
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Fix 1 for position data
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        glBindVertexArray(vaoHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(programHandle);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

GLuint BasicTriangleWithDrawElements()
{
    char vertPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/basic.vert";
    char fragPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/basic.frag";

    char * vertText = LoadShaderAsString(vertPath);
    char * fragText = LoadShaderAsString(fragPath);

    GLuint vertShader = LoadShaderObject(GL_VERTEX_SHADER, vertText);
    GLuint fragShader = LoadShaderObject(GL_FRAGMENT_SHADER, fragText);

    GLuint num = 2;
    GLuint shaders[] = {vertShader, fragShader};

    GLuint programHandle = LoadShaderProgram(shaders, num);

    GLuint vaoHandle;

    float positionData[] {
            -0.5f,  0.0f, 0.0f,
            -0.25f,-0.4f, 0.0f,
            0.0f,  0.0f, 0.0f,
            0.25f,-0.4f, 0.0f,
            0.5f,  0.0f, 0.0f
    };

    float colorData[] {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
    };

    unsigned short indexes[] = {
            0,1,2,1,3,2,2,3,4
    };

    // Create and fill buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    // Fill coordinate buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

    // Fill color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

    GLuint iboHandle;
    glGenBuffers(1, &iboHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    // Create vertex array object
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    // Activate arrays of vertex attributes
    glEnableVertexAttribArray(0); //Position
    glEnableVertexAttribArray(1); // Color

    // Fix 0 for position data
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Fix 1 for position data
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);


    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        glBindVertexArray(vaoHandle);
        glDrawElements(GL_TRIANGLES, sizeof(indexes) / sizeof(short), GL_UNSIGNED_SHORT, 0);
        UseShaderProgram(programHandle);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(programHandle);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void UniformSquareAndCicrcle()
{
    char vertPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/basic.vert";
    char fragPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/basic.frag";

    char * vertText = LoadShaderAsString(vertPath);
    char * fragText = LoadShaderAsString(fragPath);

    GLuint vertShader = LoadShaderObject(GL_VERTEX_SHADER, vertText);
    GLuint fragShader = LoadShaderObject(GL_FRAGMENT_SHADER, fragText);

    GLuint num = 2;
    GLuint shaders[] = {vertShader, fragShader};

    GLuint programHandle = LoadShaderProgram(shaders, num);
    UseShaderProgram(programHandle);

    GLuint vaoHandle;

    float positionData[] {
            -0.8, -0.8, 0.0,
            0.8, -0.8, 0.0,
            0.0, 0.8, 0.0
    };
    float colorData[] {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
    };

    // Create and fill buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    // Fill coordinate buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_DYNAMIC_DRAW);

    // Fill color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_DYNAMIC_DRAW);

    // Create vertex array object
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    // Activate arrays of vertex attributes
    glEnableVertexAttribArray(0); //Position
    glEnableVertexAttribArray(1); // Color

    // Fix 0 for position data
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Fix 1 for position data
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    PrintActiveAttributes(programHandle);
    PrintActiveUniforms(programHandle);

    float angle = 0;
    while(!glfwWindowShouldClose(window))
    {
        angle += 0.01;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();


        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0.0,0.0,1.0));
        GLuint location = glGetUniformLocation(programHandle, "RotationMatrix");
       // printf("Location %i\n", location);

        if (location >= 0)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
        }

        glBindVertexArray(vaoHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(programHandle);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void BlobInSquare()
{
    char vertPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/BlobInSq.vert";
    char fragPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/BlobInSq.frag";

    //char vertPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/basic.vert";
    //char fragPath[] = "/Users/egororachyov/Desktop/Documents/CLion/OpenGL-GLSL/Shaders/basic.frag";

    char * vertText = LoadShaderAsString(vertPath);
    char * fragText = LoadShaderAsString(fragPath);

    GLuint vertShader = LoadShaderObject(GL_VERTEX_SHADER, vertText);
    GLuint fragShader = LoadShaderObject(GL_FRAGMENT_SHADER, fragText);

    GLuint num = 2;
    GLuint shaders[] = {vertShader, fragShader};

    GLuint programHandle = LoadShaderProgram(shaders, num);
    UseShaderProgram(programHandle);

    GLuint vaoHandle;

    float positionData[] {
            -0.8, 0.8, 0,
            -0.8, -0.8, 0,
            0.8, -0.8, 0,
            0.8, 0.8, 0
    };
    float textData[] {
            0.0, 1.0, 0.0,
            0.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
            1.0, 1.0, 0.0
    };
    GLushort indexes[] = {
            0, 1, 2, 0, 2, 3
    };

    // Create and fill buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    // Fill coordinate buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

    // Fill color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textData), textData, GL_STATIC_DRAW);

    GLuint iboHandle;
    glGenBuffers(1, &iboHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    // Create vertex array object
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    // Activate arrays of vertex attributes
    glEnableVertexAttribArray(0); //Position
    glEnableVertexAttribArray(1); // Color

    // Fix 0 for position data
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Fix 1 for position data
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);

    PrintActiveAttributes(programHandle);
    PrintActiveUniforms(programHandle);

    GLuint blockIndex = glGetUniformBlockIndex(programHandle, "BlobSettings");

    GLint blockSize;
    glGetActiveUniformBlockiv(programHandle, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

    GLubyte * blockBuffer = (GLubyte*)malloc(blockSize);

    const GLchar * names[] = {"InnerColor", "OuterColor", "RadiusInner", "RadiusOuter"};

    GLuint indices[4];
    glGetUniformIndices(programHandle, 4, names, indices);

    GLint offset[4];
    glGetActiveUniformsiv(programHandle, 4, indices, GL_UNIFORM_OFFSET, offset);

    for(int i = 0; i < 4; i++) {printf("%i %i \n", indices[i], offset[i]);}

    GLfloat outerColor[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat innerColor[] = {0.78, 0.6, 0.75, 1.0};
    GLfloat innerRadius = 0.25;
    GLfloat outerRadius = 0.45;

    memcpy(blockBuffer + offset[0], innerColor, sizeof(innerColor));
    memcpy(blockBuffer + offset[1], outerColor, sizeof(outerColor));
    memcpy(blockBuffer + offset[2], &innerRadius, sizeof(GLfloat));
    memcpy(blockBuffer + offset[3], &outerRadius, sizeof(GLfloat));

    GLuint uboHandle;
    glGenBuffers(1, &uboHandle);
    glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
    glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);


    GLint location = glGetUniformLocation(programHandle, "BlobSettings.RadiusOuter");
    printf("location %i\n", location);

    float angle = 0.0;
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        glBindVertexArray(vaoHandle);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboHandle);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,0);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(programHandle);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

int main(int argc, char ** argv)
{
    InitContext();
    //PrintContextInfo();
    window = GetCurrentContext();

    UniformSquareAndCicrcle();

    DestroyContext();
    return 0;
}
