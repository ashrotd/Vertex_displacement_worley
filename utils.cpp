

#include "utils.h"

#include <soil2/SOIL2.h>


GLuint utils:: createShaderProgram(const char *vp, const char *tCS, const char *tES, const char *fp){

    GLint vertCompiled;
    GLint tcCompiled;
    GLint teCompiled;
    GLint fragCompiled;
    GLint linked;

    std::string vertShaderStr = readShaderSource(vp);
    std::string tcShaderStr = readShaderSource(tCS);
    std::string teShaderStr = readShaderSource(tES);
    std::string fragShaderStr = readShaderSource(fp);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *tcShaderSrc = tcShaderStr.c_str();
    const char *teShaderSrc = teShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint tcShader = glCreateShader(GL_TESS_CONTROL_SHADER);
    GLuint teShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vShader, 1, &vertShaderSrc, NULL);
    glShaderSource(tcShader, 1, &tcShaderSrc, NULL);
    glShaderSource(teShader, 1, &teShaderSrc, NULL);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);

    //After loading, it compiles the code
    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
    std::cout << "vertex compilation failed" << std::endl;
    printShaderLog(vShader);
    }

     glCompileShader(tcShader);
    checkOpenGLError();
    glGetShaderiv(tcShader, GL_COMPILE_STATUS, &tcCompiled);
    if (tcCompiled != 1) {
    std::cout << "vertex compilation failed" << std::endl;
    printShaderLog(tcShader);
    }

    glCompileShader(teShader);
    checkOpenGLError();
    glGetShaderiv(teShader, GL_COMPILE_STATUS, &teCompiled);
    if (teCompiled != 1) {
    std::cout << "vertex compilation failed" << std::endl;
    printShaderLog(teShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
    std::cout << "fragment compilation failed" << std::endl;
    printShaderLog(fShader);
    }

    // A program object saves ID that points to it
    GLuint vfProgram = glCreateProgram();

    // Attaches each of the shader to the program
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, tcShader);
    glAttachShader(vfProgram, teShader);
    glAttachShader(vfProgram, fShader);

    //Requests the GLSL compiles ensure that they are compatible
    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
    std::cout << "linking failed" << std::endl;
     printProgramLog(vfProgram);
    }
    return vfProgram;
}

    std::string utils::readShaderSource(const char* filepath){
    std::string content;
    std::ifstream fileStream(filepath,std::ios::in);
    std::string line="";

    while(!fileStream.eof()){
        getline(fileStream,line);
        content.append(line+"\n");
    }
    fileStream.close();
    return content;
}

// Since GLSL runs in c++ runtime its difficult
// to find the error in the compilation
// or linking or simple OpenGL errors

// These 3 functions help in finding the errors

//Program 2.3 Modules to Catch GLSL Errors

void utils::printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char *)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        std::cout << "Shader Info Log: " << log << std::endl;
        free(log);
    } 
}
void utils::printProgramLog(int prog) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char *)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        std::cout << "Program Info Log: " << log << std::endl;
        free(log);
    } 
}
bool utils::checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        std::cout << "glError: " << glErr << std::endl;
        foundError = true;
        glErr = glGetError();
    }
return foundError;
}

GLuint utils::loadTexture(const char* texImagePath){
    GLuint textureID;
    textureID = SOIL_load_OGL_texture(texImagePath,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    if(textureID==0) std::cout<<"Couldn't find the texture file"<<texImagePath<<std::endl;
    return textureID;
}

    

    
