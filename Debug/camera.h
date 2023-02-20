// Lawrence Arundel CS 330 7-1 Submit Project
/* This file originated from website LearnOpenGL.com, which distributes the code
with the following information regarding licensing:
All code samples, unless explicitly stated otherwise, are licensed under the terms
of the CC BY-NC 4.0 license as published by Creative Commons, either version 4 of
the License, or (at your option) any later version. You can find a human-readable format of the license
https://creativecommons.org/licenses/by-nc/4.0/
and the full license
https://creativecommons.org/licenses/by-nc/4.0/legalcode
*/

// checking camera_h to see if macro is not defined (IBM, 2021, p. 1)
#ifndef CAMERA_H
#define CAMERA_H

// header files that are used for the glm math functions (Chapman, 2020, p. 1)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// utilizes vector functions with vector library (Chapman, 2020, p. 1)
#include <vector>

// enumeration that defines the movement of the camera (Chapman, 2020, p. 1)
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// camera values that specify the yaw, pitch, speed, sensitivity, and zoom properties for camera (Chapman, 2020, p. 1)
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// camera class that defines the various properties that handle various functions throughout the project (Chapman, 2020, p. 1)
class Camera
{
public:
	// various camera attributes (Chapman, 2020, p. 1)
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// euler angles used for orientation of image (Chapman, 2020, p. 1)
	float Yaw;
	float Pitch;

	// camera options that are used to control movement speed, mouse sensitivity, and zoom (Chapman, 2020, p. 1)
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// camera constructor that sets the various vectors on the x, y and z axis (Chapman, 2020, p. 1)
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// camera constructor that sets the various vectors on the x, y and z axis with scalar options (Chapman, 2020, p. 1)
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// returns the euler angles to construct the posotion of image utilizing euler angles (Chapman, 2020, p. 1)
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	/// <summary>
	/// handles input from every keyboard - like input device.accepts an input parameter that is an ENUM defined by the 
	/// camera(to abstract it from windowing systems) (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="deltaTime"></param>
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
	}

	/// <summary>
	/// handles input from the mouse input system.both the x and y 
	/// directions of the offset value are expected (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="xoffset"></param>
	/// <param name="yoffset"></param>
	/// <param name="constrainPitch"></param>
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		// multiply the xoffset by the mouse sensitivity variable and also for yoffset variable (Chapman, 2020, p. 1)
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		// add to yaw variable from the xoffset variable (Chapman, 2020, p. 1)
		Yaw += xoffset;

		// add to pitch variable from the yoffset variable (Chapman, 2020, p. 1)
		Pitch += yoffset;

		// ensure that the screen doesn't flip when the pitch goes out of bounds (Chapman, 2020, p. 1)
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// using the modified Euler angles, update the Front, Right, and Up vectors (Chapman, 2020, p. 1)
		updateCameraVectors();
	}

	/// <summary>
	/// executes commands in response to a mouse scroll - wheel event input is only needed 
	/// for the vertical wheel axis (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="yoffset"></param>
	void ProcessMouseScroll(float yoffset)
	{
		// subtract from zoom the y offset variable
		// if zoom variable less than 1.0, set it to 1.0 as constraint
		// if zoom variable exceed 45.0, set it to 45.0 as constraint (Chapman, 2020, p. 1)
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

private:
	/// <summary>
	/// // from the Camera's, / calculates the front vector (updated) Angles of Euler (Chapman, 2020, p. 1)
	/// </summary>
	void updateCameraVectors()
	{
		// operations that calculate the new front camera variable (Chapman, 2020, p. 1)
		glm::vec3 front{};
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		// recalculates the right and up vectors to re position camera during execution (Chapman, 2020, p. 1)
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
#endif