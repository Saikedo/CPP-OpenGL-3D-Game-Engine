#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};


class Camera
{
public:
	
	static Camera* getCameraInstance();

	~Camera();

	glm::mat4 getCameraView();
	void setPitch(float newPitch);
	void changePitch(float dPitch);
	void setYaw(float newYaw);
	void changeYaw(float dYaw);
	float getZoom() { return Zoom; }
	float setZoom(float newZoom) { Zoom = newZoom; }
	float changeZoom(float dZoom) { Zoom += dZoom; }
	float getMovementSpeed() { return MovementSpeed;}
	float setMovementSpeed(float newMovementSpeed) { MovementSpeed = newMovementSpeed; }
	void move(CameraMovement direction, float deltaTime);
	glm::vec3 getPosition() {return Position;}
	void update();

private:
	static Camera * instance;
	Camera();

	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Eular Angles
	float Yaw;
	float Pitch;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
};