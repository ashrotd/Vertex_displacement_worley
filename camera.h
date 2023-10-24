// camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float speed;
    float yaw;   // Horizontal angle
    float pitch; // Vertical angle

    // Sensitivity affects how much the camera angle changes for mouse movement
    float mouseSensitivity; 

    Camera(); // Constructor

    // Function to respond to keyboard input
    void processKeyboard(int key);

    // Function to respond to mouse movement
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch);

    void processMouseScroll(float yoffset);

private:
    // Calculates the front vector from the Camera's updated Euler Angles
    void updateCameraVectors();
    // other declarations...
};

#endif  // CAMERA_H
