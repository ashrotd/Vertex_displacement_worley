// camera.cpp
#include "camera.h"
#include "GLFW/glfw3.h"
Camera::Camera() {
    // Set initial values for the camera position, target, up, etc.
    // For example:
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    target = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 0.5f;
    mouseSensitivity = 0.05f;
    // ... other initializations ...
}

void Camera::processKeyboard(int key) {
    switch (key) {
        case GLFW_KEY_W:
            position += speed * target; // "this" is implied here
            break;
        case GLFW_KEY_S:
            position -= speed * target; // Moving backward
            break;
        case GLFW_KEY_A:
            // Move left; the cross product will give you the vector pointing left
            position -= glm::normalize(glm::cross(target, up)) * speed;
            break;
        case GLFW_KEY_D:
            // Move right; the cross product will give you the vector pointing right
            position += glm::normalize(glm::cross(target, up)) * speed;
            break;
        case GLFW_KEY_Q:
            // Move the camera down
            position -= up * speed;  // Decrease the y-coordinate of the camera's position
            break;
        case GLFW_KEY_E:
            // Move the camera up
            position += up * speed;  // Increase the y-coordinate of the camera's position
            break;
        case GLFW_KEY_ESCAPE:
            // This action is not appropriate to handle here, as the Camera class shouldn't handle window events directly.
            // Consider handling this in the key callback function or somewhere relevant where the window object is accessible.
            break;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch -= yoffset; // Reversed since y-coordinates range from bottom to top

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    // Update target, Right and Up Vectors using the updated Euler angles (yaw and pitch)
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    // Calculate the new target vector based on yaw and pitch; the target is the direction the camera is facing
    glm::vec3 newTarget;
    newTarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newTarget.y = sin(glm::radians(pitch));
    newTarget.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    target = glm::normalize(newTarget);

    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    // Right vector
    glm::vec3 right = glm::normalize(glm::cross(target, glm::vec3(0.0f, 1.0f, 0.0f))); 
    // Up vector
    up = glm::normalize(glm::cross(right, target));
}
