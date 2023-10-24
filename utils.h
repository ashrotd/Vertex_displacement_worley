#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>



class utils{


public:
    utils(){}
        
public:

    static std::string readShaderSource(const char *filePath);
    static GLuint createShaderProgram(const char *vp, const char *tCS, const char *tES, const char *fp);
    static void printShaderLog(GLuint shader);
    static void printProgramLog(int prog);
    static bool checkOpenGLError();
    static GLuint loadTexture(const char* texImagePath);

};