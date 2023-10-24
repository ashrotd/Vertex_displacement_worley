#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "uu.h"
#include "camera.h"
#include <functional>
#include <random>
#include <array>

std::vector<unsigned int> indices;
using HeightGenerator = std::function<float(float, float)>;
 GLuint shaderProgram;
 Camera camera;
 GLuint texture;
std::vector<float> gridVertices;
GLuint VBO, VAO,EBO;
float displacement = 0.0f;
float frequency = 0.5f;
float amplitude = 3.0f;
float phase = 0.1f;
GLuint worleyTexture;

std::vector<unsigned int> generateTerrainIndices(unsigned int gridSize) {
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < gridSize; ++i) {
        for (unsigned int j = 0; j < gridSize; ++j) {
            int topLeft = (i * (gridSize + 1)) + j;
            int topRight = topLeft + 1;
            int bottomLeft = ((i + 1) * (gridSize + 1)) + j;
            int bottomRight = bottomLeft + 1;

            //First triangle
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            //Second triangle
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    return indices;
}

std::vector<float> generateGridVertices(unsigned int size, const HeightGenerator& heightFunc) {
    std::vector<float> vertices;
    for (unsigned int i = 0; i <= size; ++i) {
        for (unsigned int j = 0; j <= size; ++j) {
            float x = (float)i;
            float z = (float)j;
            float y = heightFunc(x, z);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            vertices.push_back((float)i / size);
            vertices.push_back((float)j / size); 
        }
    }
    return vertices;
}
float sineHeightFunction(float x, float z) {
    return amplitude * std::sin(frequency * x + phase) * std::cos(frequency * z + phase);
}

std::vector<float> generateWorleyNoise(unsigned textureSize) {
    std::vector<float> data(textureSize * textureSize * textureSize);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    const int numPoints = 20;
    std::vector<std::array<float, 3>> points;
    
    for (int i = 0; i < numPoints; ++i) {
    std::array<float, 3> newPoint = {static_cast<float>(dis(gen))*0.5f, static_cast<float>(dis(gen))*0.5f, static_cast<float>(dis(gen))*0.5f};
    points.push_back(newPoint);
}

    for (unsigned x = 0; x < textureSize; ++x) {
        for (unsigned y = 0; y < textureSize; ++y) {
            for (unsigned z = 0; z < textureSize; ++z) {
                float minimumDistance = std::numeric_limits<float>::max();

                for (const auto& point : points) {
                    float dx = point[0] - (float)x / textureSize;
                    float dy = point[1] - (float)y / textureSize;
                    float dz = point[2] - (float)z / textureSize;
                    float distance = std::sqrt(dx * dx + dy * dy + dz * dz);

                    minimumDistance = std::min(minimumDistance, distance);
                }

                data[(z * textureSize * textureSize) + (y * textureSize) + x] = 1.0f - minimumDistance;
            }
        }
    }

    return data;
}

GLuint create3DTextureFromNoise(const std::vector<float>& noiseData, unsigned size) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_3D, textureID);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage3D(
        GL_TEXTURE_3D, 0, GL_R32F, size, size, size, 0, GL_RED, GL_FLOAT, noiseData.data()
    );

    glBindTexture(GL_TEXTURE_3D, 0);  

    return textureID;
}


void init(GLFWwindow* window) {

    camera = Camera();
    shaderProgram = uu::createShaderProgram("../v.glsl","../f.glsl");
    gridVertices = generateGridVertices(10,sineHeightFunction); // 10x10 grid
     indices = generateTerrainIndices(10);
    unsigned textureSize = 64;  // Size of the 3D texture
    auto noiseData = generateWorleyNoise(textureSize);
    worleyTexture = create3DTextureFromNoise(noiseData, textureSize);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}
// Callback for handling GLFW errors
void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                frequency += 0.05f; 
                break;
            case GLFW_KEY_DOWN:
                frequency -= 0.05f; 
                break;
            case GLFW_KEY_RIGHT:
                amplitude += 0.5f; 
                break;
            case GLFW_KEY_LEFT:
                amplitude -= 0.5f; 
                break;
            case GLFW_KEY_SPACE: 
                phase += 0.1f;
                break;
         
        }
        camera.processKeyboard(key); 
    }
}

void display(GLFWwindow* window, double currentTime){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2,0.4,0.6,1.0);
    glEnable(GL_DEPTH_TEST); 
    glClear(GL_DEPTH_BUFFER_BIT); 

    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f); 
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
     glUniform1f(glGetUniformLocation(shaderProgram, "displacement"), displacement); 
    

    float timeValue = glfwGetTime();  // Get time
    int timeLocation = glGetUniformLocation(shaderProgram, "time");
    glUniform1f(timeLocation, timeValue);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, worleyTexture);

    glUniform1f(glGetUniformLocation(shaderProgram, "time"), (float)currentTime);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    GLenum err;
while((err = glGetError()) != GL_NO_ERROR) {
    std::cerr << "OpenGL error: " << err << std::endl;
}
}

int main() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1200, 800, "Grid Manipulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    init(window);
    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
