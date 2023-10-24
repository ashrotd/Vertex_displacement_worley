#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>



class uu{


public:
    uu(){}
        
public:

    static std::string readShaderSource(const char *filePath);
    static GLuint createShaderProgram(const char* filepath1,const char* filepath2);
    static void printShaderLog(GLuint shader);
    static void printProgramLog(int prog);
    static bool checkOpenGLError();
    static GLuint loadTexture(const char* texImagePath);

};