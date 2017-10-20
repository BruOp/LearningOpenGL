#pragma once

#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera();
    Camera(glm::vec3 position);
    Camera(glm::vec3 position, glm::vec3 front);

    inline glm::vec3 getPosition() const { return _position; };
    inline glm::vec3 getFront() const { return _front; };
    inline glm::vec3 getUp() const { return _up; };
    inline glm::vec3 getRight() const { return _right; };

    inline GLfloat getYaw() const { return _yaw; };
    inline GLfloat getPitch() const { return _pitch; };
    inline GLfloat getZoom() const { return _zoom; };

    void updateCameraVectors();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(GLint width, GLint height) const;

    // Input related stuff
    void processKeyboard(CameraMovement movementDirection, GLfloat deltaTime);
    void processMouseMovement(GLfloat xOffset, GLfloat yOffset);
    void processMouseScroll(GLfloat scrollOffset);

private:
    // Position and 
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp;

    GLfloat _yaw;
    GLfloat _pitch;
    GLfloat _zoom;

    GLfloat _sensitivity;
    GLfloat _movementSpeed;
};
