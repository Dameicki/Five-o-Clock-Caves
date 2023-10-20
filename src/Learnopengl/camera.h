#pragma once
#define CAMERA Camera::GetInstance()

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "core/InputManager.h"
#include "Core/Time.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods


// Default camera values
const float YAW = -45.0f;
const float PITCH = -45.0f;
const float SPEED = 7.0f;
const float SENSITIVITY = 0.2f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
    bool isEditorMode = false;
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    unsigned int SCR_WIDTH = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    unsigned int SCR_HEIGHT = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

    static Camera& GetInstance()
    {
        static Camera* instance = NULL;

        if (instance == NULL)
            instance = new Camera();

        return *instance;
    }
    void SetUp(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH){
        Front = glm::vec3(0.0f, 0.0f, -1.0f);
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Zoom = ZOOM;
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with vectors
    /*
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }*/

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(GLboolean constrainPitch = true)
    {
        if (INPUT.GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {

            glm::vec2 offset = INPUT.GetMouseOffset();


            offset.x *= MouseSensitivity;
            offset.y *= MouseSensitivity;


            Yaw += offset.x;
            Pitch += offset.y;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch)
            {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }

            // update Front, Right and Up Vectors using the updated Euler angles
            updateCameraVectors();
        }
    }

	void setIsEditorMode(bool value)
    {
        isEditorMode = value;
    }
    bool getIsEditorMode() const
    {
        return isEditorMode;
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    void SetLookDir(glm::vec3 newLookDir)
    {
        Front = glm::normalize(newLookDir);
        Right = glm::normalize(glm::cross(Front, WorldUp)); 
        Up = glm::normalize(glm::cross(Right, Front));
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};