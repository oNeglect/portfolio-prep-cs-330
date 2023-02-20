// Lawrence Arundel CS 330 7-1 Submit Project
#pragma once

// include file with the proper properties for vertex class for construction of objects within environment (Chapman, 2020, p. 1)
#include "Vertex.h"

// include / header file that holds all OpenGL type declarations (Chapman, 2020, p. 1)
#include <glad/glad.h>

// structure used to determine the vertices, indices, number of each, and the construction of vertices for objects within project (Chapman, 2020, p. 1)
struct ShapeData
{
	// constructor used to determine the shape data for each object (Chapman, 2020, p. 1)
	ShapeData() :
		vertices(0), numVertices(0),
		indices(0), numIndices(0) {}
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;
	GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}

	/// <summary>
	/// function used to clean the data after construction of shape (Chapman, 2020, p. 1)
	/// </summary>
	void cleanup()
	{
		delete[] vertices;
		delete[] indices;
		numVertices = numIndices = 0;
	}
};