#include "camera.h"
#include <iostream>
Camera * Camera::instance;

Camera::Camera()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw = -90.0f;
	Pitch = 0.0f;
	Zoom = 90.0f;
	MovementSpeed = 50.0f;
	update();
}


Camera::~Camera()
{
	delete instance;
}


Camera* Camera::getCameraInstance()
{
	if (instance == NULL)
	{
		instance = new Camera();
	}

	return instance;
}

glm::mat4 Camera::getCameraView()
{
	return glm::lookAt(Position, Position + Front, Up);
}


void Camera::update()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);


	// Also re-calculate the Right and Up vector
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Right = glm::normalize(glm::cross(Front, WorldUp));  
	Up = glm::normalize(glm::cross(Right, Front));


	//std::cout << "Pitch: " << pitch << " Yaw: " << yaw << std::endl;
}



void Camera::move(CameraMovement direction, float dt)
{
	float velocity = MovementSpeed * dt;

	switch (direction)
	{
	case FORWARD:
	{
		Position += Front * velocity;
		break;
	}
	case BACKWARD:
	{
		Position -= Front * velocity;
		break;
	}
	case LEFT:
	{
		Position -= Right * velocity;
		break;
	}
	case RIGHT:
	{
		Position += Right * velocity;
		break;
	}
	case UP:
	{
		Position += Up * velocity;
		break;
	}
	case DOWN:
	{
		Position -= Up * velocity;
		break;
	}

	}

}

void Camera::setPitch(float newPitch)
{
	if (newPitch > 89.0f)
	{
		Pitch = 89.0f;
	}
	else if (newPitch < -89.0f)
	{
		Pitch = -89.0f;
	}
	else
	{
		Pitch = newPitch;
	}
}


void Camera::changePitch(float dPitch)
{
	Pitch += dPitch;

	if (Pitch > 89.0f)
	{
		Pitch = 89.0f;
	}
	else if (Pitch < -89.0f)
	{
		Pitch = -89.0f;
	}
}


void Camera::setYaw(float newYaw)
{
	Yaw = newYaw;
}

void Camera::changeYaw(float dYaw)
{
	Yaw += dYaw;
}