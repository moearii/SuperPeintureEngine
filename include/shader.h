#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

class Shader
{
    public:
        // The program ID
        GLuint Program;
        // Constructor reads and builds the shader
        Shader();
        void init(const GLchar* vertexPath, const GLchar* fragmentPath);
        void initComputeShader(const GLchar* computeShaderPath);
        // Use the program
        void use();

    private:

        void printWorkGroupsCapabilities();
};

#endif
