#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "utils.h"
#include "camera.h"
GLuint renderingProgram;
GLuint vao, vbo;
GLuint mvpLoc;
GLuint projLoc,mvLoc;
int width,height;
float aspect;
glm::mat4 pMat,vMat,projMat,mvMat,mMat;
float cameraX,cameraY,cameraZ;
float pryLocX,pryLocY,pryLocZ;
GLuint brickTexture;
const GLuint WIDTH = 800, HEIGHT = 600;
// // Global camera
Camera camera;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
struct Light {
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

// Define a Material in your application
struct Material {
    GLuint diffuse; // This is your texture
    glm::vec3 specular;
    float shininess;
};


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
    renderingProgram = utils::createShaderProgram("../bezvert.glsl","../beztc.glsl","../bezte.glsl","../bezfrag.glsl");
    brickTexture = utils::loadTexture("brick1.jpg");
    setupVertices();
    camera = Camera();
    //cameraX = 0.0f,cameraY=5.0f,cameraZ=8.0f;
    pryLocX = 1.0f,pryLocY=2.0f,pryLocZ=-8.0f;

}

void display(GLFWwindow* window, double currentTime, const Light& light, const Material& material) {
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

    GLuint lightPosLoc = glGetUniformLocation(renderingProgram, "light.position");
    GLuint lightAmbientLoc = glGetUniformLocation(renderingProgram, "light.ambient");
    GLuint lightDiffuseLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
    GLuint lightSpecularLoc = glGetUniformLocation(renderingProgram, "light.specular");

    glUniform3f(lightPosLoc, light.position.x, light.position.y, light.position.z);
    glUniform3f(lightAmbientLoc, light.ambient.x, light.ambient.y, light.ambient.z);
    glUniform3f(lightDiffuseLoc, light.diffuse.x, light.diffuse.y, light.diffuse.z);
    glUniform3f(lightSpecularLoc, light.specular.x, light.specular.y, light.specular.z);

    // Set material properties
    // As with the light, you need to access each property in the struct
    GLuint matDiffuseLoc = glGetUniformLocation(renderingProgram, "material.diffuse");
    GLuint matSpecularLoc = glGetUniformLocation(renderingProgram, "material.specular");
    GLuint matShineLoc = glGetUniformLocation(renderingProgram, "material.shininess");

    glUniform1i(matDiffuseLoc, 0); // we bound our texture to texture unit 0 earlier
    glUniform3f(matSpecularLoc, material.specular.x, material.specular.y, material.specular.z);
    glUniform1f(matShineLoc, material.shininess);

// Also, don't forget to update the view position if it changes
    GLuint viewPosLoc = glGetUniformLocation(renderingProgram, "viewPos");
    glUniform3f(viewPosLoc, camera.position.x, camera.position.y, camera.position.z);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, brickTexture);
    glFrontFace(GL_CCW);
    glPatchParameteri(GL_PATCH_VERTICES, 16); // number of vertices per patch = 16
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_PATCHES, 0, 16);

         GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
     std::cout << "Mouse Position X: " << xpos << " Y: " << ypos << std::endl;

     float xoffset = (xpos - lastX) * camera.mouseSensitivity;
    float yoffset = (lastY - ypos) * camera.mouseSensitivity; // Reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    // Here, we're passing 'true' for the 'constrainPitch' parameter. You can adjust this based on your needs.
    camera.processMouseMovement(xoffset, yoffset, true); 
}
int main(void) {
    Light light;
    light.position = glm::vec3(1.0f, 0.0f,-8.0f); // example position
    light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f); // moderate white light
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f); // bright white light

    Material material;
    material.diffuse = brickTexture; // assuming you loaded this earlier
    material.specular = glm::vec3(0.5f, 0.5f, 0.5f); // some specular highlight
    material.shininess = 32.0f;
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Bezier Curve", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime(),light,material);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        camera.processKeyboard(key);
    }
}




// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//     camera.processMouseScroll(yoffset);
// }