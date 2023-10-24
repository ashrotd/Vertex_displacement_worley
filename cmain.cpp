#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "utils.h"

GLuint renderingProgram;
GLuint vao, vbo;
GLuint mvpLoc;
GLuint projLoc,mvLoc;
int width,height;
float aspect;
glm::mat4 pMat,vMat,projMat,mvMat,mMat;
float cameraX,cameraY,cameraZ;
float pryLocX,pryLocY,pryLocZ;
void setupVertices() {
    // Define vertex data for a single patch or quad
    GLfloat vertices[] = {
        0.0f, 0.0f, 0.0f  // Vertex position
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Assuming you have a position attribute in your vertex shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void init(GLFWwindow* window) {
    renderingProgram = utils::createShaderProgram("../vert.glsl","../tc.glsl","../te.glsl","../frag.glsl");
setupVertices();
cameraX = 0.0f,cameraY=0.0f,cameraZ=8.0f;
    pryLocX = 0.0f,pryLocY=0.0f,pryLocZ=-8.0f;
}

void display(GLFWwindow* window, double currentTime) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

    glUseProgram(renderingProgram);
    
    //build the perspective matrix
    glfwGetFramebufferSize(window,&width,&height);
    aspect = float(width)/(float) height;
    pMat = glm::perspective(1.0472f,aspect,0.1f,1000.0f);
    
    //build view Matrix
    vMat = glm::translate(glm::mat4(1.0f),glm::vec3(-cameraX,-cameraY,-cameraZ));
    mMat = glm::translate(glm::mat4(1.0f),glm::vec3(pryLocX,pryLocY,pryLocZ));

    mvMat=pMat*vMat*mMat;

    // Drawing the cube
    glUniformMatrix4fv(mvLoc,1,GL_FALSE,glm::value_ptr(mvMat));

    glPatchParameteri(GL_PATCH_VERTICES, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_PATCHES, 0, 1);
}

int main(void) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(1200, 800, "Tessellation Shader Example", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);
    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
