#include "Camera.h"

// Default camera values
const GLfloat gPi = glm::pi<GLfloat>();
const GLfloat YAW = -0.5 * gPi;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

const GLfloat MIN_PITCH = glm::radians(-89.0f);
const GLfloat MAX_PITCH = glm::radians(89.0f);

const GLfloat MIN_ZOOM = 1.0f;
const GLfloat MAX_ZOOM = 45.0f;

Camera::Camera() :
    Camera(glm::vec3(0.0f))
{
}

Camera::Camera(glm::vec3 position) :
    Camera(position, glm::vec3(0.0f, 0.0f, 1.0f))
{
}

Camera::Camera(glm::vec3 position, glm::vec3 front) :
    _position(position),
    _front(front),
    _worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    _yaw(YAW),
    _pitch(PITCH),
    _zoom(ZOOM),
    _sensitivity(SENSITIVTY),
    _movementSpeed(SPEED)
{
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = glm::cos(_yaw) * glm::cos(_pitch);
    front.y = glm::sin(_pitch);
    front.z = glm::cos(_pitch) * glm::sin(_yaw);
    _front = glm::normalize(front);
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera::getProjectionMatrix(GLint width, GLint height) const
{
    return glm::perspective(_zoom, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime)
{
    GLfloat velocity = _movementSpeed * deltaTime;
    if (direction == FORWARD)
        _position += _front * velocity;
    else if (direction == BACKWARD)
        _position -= _front * velocity;
    else if (direction == RIGHT)
        _position += _right * velocity;
    else if (direction == LEFT)
        _position -= _right * velocity;
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset)
{
    // This function updates the yaw and pitch of the camera using xOffset and yOffset.
    // Since yaw and pitch are in radians, we must convert the distance values appropriately.
    // Additionally, it constrains to pitch (to prevent gimbal lock, b/c euler angles are bad)

    _yaw += glm::radians(xOffset * _sensitivity);
    _pitch += glm::radians(yOffset * _sensitivity);

    _pitch = glm::clamp(_pitch, MIN_PITCH, MAX_PITCH);

    updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat scrollOffset)
{
    _zoom += scrollOffset;
    _zoom = glm::clamp(_zoom, MIN_ZOOM, MAX_ZOOM);
}
