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

//Camera Setup
struct Camera {
    glm::vec3 position;
    glm::vec3 target;  // Usually it points out of the screen
    glm::vec3 up;
    float speed;
};

// // Global camera
Camera camera;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


void setupVertices(){
    
    float vertices[] = { 0.0f, 0.0f, 0.0f }; // Just a single point
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao);
}

void init(GLFWwindow* window) {
    renderingProgram = utils::createShaderProgram("../vert.glsl","../tc.glsl","../te.glsl","../frag.glsl");
    setupVertices();
    //cameraX = 0.0f,cameraY=5.0f,cameraZ=8.0f;
    pryLocX = 0.0f,pryLocY=2.0f,pryLocZ=-8.0f;
    camera.position = glm::vec3(0.0f, 5.0f, 8.0f);
    camera.target = glm::vec3(0.0f, 0.0f, -1.0f);
    camera.up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera.speed = 0.05f;
    
}

void display(GLFWwindow* window, double currentTime) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

    glUseProgram(renderingProgram);
    
    mvLoc = glGetUniformLocation(renderingProgram, "mvp_matrix");
// Check other uniform locations similarly
    if (mvLoc == -1) {
    // handle error, e.g., output some debug information
    std::cerr << "Can't find uniform location." << std::endl;
}
    //build the perspective matrix
    glfwGetFramebufferSize(window,&width,&height);
    aspect = float(width)/(float) height;
    pMat = glm::perspective(1.0472f,aspect,0.1f,1000.0f);
    
    //build view Matrix
    vMat = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
   
    mMat = glm::translate(glm::mat4(1.0f),glm::vec3(pryLocX,pryLocY,pryLocZ));

    mvMat=pMat*vMat*mMat;

    // Drawing the cube
    glUniformMatrix4fv(mvLoc,1,GL_FALSE,glm::value_ptr(mvMat));

    glPatchParameteri(GL_PATCH_VERTICES, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_PATCHES, 0, 1);

         GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
}

int main(void) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(1200, 800, "Tessellation Shader Example", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                camera.position += camera.speed * camera.target;
                break;
            case GLFW_KEY_S:
                camera.position -= camera.speed * camera.target;
                break;
            case GLFW_KEY_A:
                camera.position -= glm::normalize(glm::cross(camera.target, camera.up)) * camera.speed;
                break;
            case GLFW_KEY_D:
                camera.position += glm::normalize(glm::cross(camera.target, camera.up)) * camera.speed;
                break;
           case GLFW_KEY_Q:  // Move the camera down
                camera.position -= camera.up * camera.speed;  // Decrease the y-coordinate of the camera's position
                break;
            case GLFW_KEY_E:  // Move the camera up
                camera.position += camera.up * camera.speed;  // Increase the y-coordinate of the camera's position
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);  // Close the application if 'ESC' is pressed
                break;
        }
    }
}
