// Lawrence Arundel CS 330 7-1 Submit Project

// include file that locates functions / variables used within shape generator class (Chapman, 2020, p. 1)
#include "ShapeGenerator.h"

// header files that are used for the glm math functions (Chapman, 2020, p. 1)
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

// include file that locates functions / variables used within the vertex class (Chapman, 2020, p. 1)
#include "Vertex.h"

// variables used to construct sphere in project (Chapman, 2020, p. 1)
constexpr auto PI = 3.14159265359;
using glm::vec3;
using glm::mat4;
using glm::mat3;
#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

// randomize color generator for the shape being generated within the class (Chapman, 2020, p. 1)
glm::vec3 randomColor()
{
	glm::vec3 ret{};
	ret.x = rand() / (float)RAND_MAX;
	ret.y = rand() / (float)RAND_MAX;
	ret.z = rand() / (float)RAND_MAX;
	return ret;
}

/// <summary>
/// function that constructs the vertices of the plane object utilizing the passed dimensions variable (Chapman, 2020, p. 1)
/// </summary>
/// <param name="dimensions"></param>
/// <returns></returns>
ShapeData ShapeGenerator::makePlaneVerts(uint dimensions)
{
	// variables used to initialize various properties within the shape data object (Chapman, 2020, p. 1)
	ShapeData ret;
	ret.numVertices = dimensions * dimensions;
	int half = dimensions / 2;
	ret.vertices = new Vertex[ret.numVertices];

	// nested for loop that constructs positions for each vertex to its correct position given x, y, and z coordinates (Chapman, 2020, p. 1)
	for (int i = 0; i < dimensions; i++)
	{
		for (int j = 0; j < dimensions; j++)
		{
			Vertex& thisVert = ret.vertices[i * dimensions + j];
			thisVert.position.x = j - half;
			thisVert.position.z = i - half;
			thisVert.position.y = 0;
			thisVert.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			thisVert.color = randomColor();
		}
	}

	// return the shape data object (Chapman, 2020, p. 1)
	return ret;
}

/// <summary>
/// function used to create the plane indices within project (Chapman, 2020, p. 1)
/// </summary>
/// <param name="dimensions"></param>
/// <returns></returns>
ShapeData ShapeGenerator::makePlaneIndices(uint dimensions)
{
	// variables used to initialize various properties within the shape data object (Chapman, 2020, p. 1)
	ShapeData ret;
	ret.numIndices = (dimensions - 1) * (dimensions - 1) * 2 * 3;
	ret.indices = new unsigned short[ret.numIndices];
	int runner = 0;

	// nested for loop that constructs positions for each indices to its correct position with the array of indices (Chapman, 2020, p. 1)
	for (int row = 0; row < dimensions - 1; row++)
	{
		for (int col = 0; col < dimensions - 1; col++)
		{
			ret.indices[runner++] = dimensions * row + col;
			ret.indices[runner++] = dimensions * row + col + dimensions;
			ret.indices[runner++] = dimensions * row + col + dimensions + 1;

			ret.indices[runner++] = dimensions * row + col;
			ret.indices[runner++] = dimensions * row + col + dimensions + 1;
			ret.indices[runner++] = dimensions * row + col + 1;
		}
	}

	// assertion that indicates whether runner variable is equal to the number of indices meaning the for loop is correct (Chapman, 2020, p. 1)
	assert(runner = ret.numIndices);

	// return the shape data object (Chapman, 2020, p. 1)
	return ret;
}

/// <summary>
/// function used to create the plane indices within project (Chapman, 2020, p. 1)
/// </summary>
/// <param name="dimensions"></param>
/// <returns></returns>
ShapeData ShapeGenerator::makePlane(uint dimensions)
{
	// objects used to make the vertices and indices of plane used within project (Chapman, 2020, p. 1)
	ShapeData ret = makePlaneVerts(dimensions);
	ShapeData ret2 = makePlaneIndices(dimensions);

	// sets the indices and number of indices to the data points within shape data objects (Chapman, 2020, p. 1)
	ret.numIndices = ret2.numIndices;
	ret.indices = ret2.indices;

	// return the shape data object (Chapman, 2020, p. 1)
	return ret;
}

/// <summary>
/// shape generator class that constructs the sphere within project (Chapman, 2020, p. 1)
/// </summary>
/// <param name="tesselation"></param>
/// <returns></returns>
ShapeData ShapeGenerator::makeSphere(uint tesselation)
{
	// variable objects used to create the vertices and indices of sphere object (Chapman, 2020, p. 1)
	ShapeData ret = makePlaneVerts(tesselation);
	ShapeData ret2 = makePlaneIndices(tesselation);
	ret.indices = ret2.indices;
	ret.numIndices = ret2.numIndices;

	// attributes used to implement the calculations / construction of sphere object (Chapman, 2020, p. 1)
	uint dimensions = tesselation;
	const float RADIUS = 1.0f;
	const double CIRCLE = PI * 2;
	const double SLICE_ANGLE = CIRCLE / (dimensions - 1);

	// nested for loop begins with the construction of sphere object given above variables within calculations
	// the for loops construct the x, y , and z coordinates for the sphere and creates normalized vectors (Chapman, 2020, p. 1)
	for (size_t col = 0; col < dimensions; col++)
	{
		double phi = -SLICE_ANGLE * col;
		for (size_t row = 0; row < dimensions; row++)
		{
			double theta = -(SLICE_ANGLE / 2.0) * row;
			size_t vertIndex = col * dimensions + row;
			Vertex& v = ret.vertices[vertIndex];
			v.position.x = RADIUS * cos(phi) * sin(theta);
			v.position.y = RADIUS * sin(phi) * sin(theta);
			v.position.z = RADIUS * cos(theta);
			v.normal = glm::normalize(v.position);
		}
	}
	return ret;
}
