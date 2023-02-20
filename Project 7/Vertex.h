// Lawrence Arundel CS 330 7-1 Submit Project
#pragma once

// header files that are used for the glm math functions (Chapman, 2020, p. 1)
#include <glm\glm.hpp>

// structure used to determine vectors position, color, and normal to be used within shader of project (Chapman, 2020, p. 1)
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};
