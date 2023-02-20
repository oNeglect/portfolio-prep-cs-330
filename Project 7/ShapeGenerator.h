// Lawrence Arundel CS 330 7-1 Submit Project
#pragma once

// include file that has various properties for the shape including vertices and indices (Chapman, 2020, p. 1)
#include "ShapeData.h"

// variable to determine the demensions and tesselation of shape data object (Chapman, 2020, p. 1)
typedef unsigned int uint;

// class used to construct the various objects within project (Chapman, 2020, p. 1)
class ShapeGenerator
{
	// functions used to make the plane vertices and the plane indices within project  (Chapman, 2020, p. 1)
	static ShapeData makePlaneVerts(uint dimensions);
	static ShapeData makePlaneIndices(uint dimensions);

public:
	// functions used to make the plane object within project (Chapman, 2020, p. 1)
	static ShapeData makePlane(uint dimensions = 10);
	static ShapeData makeSphere(uint tesselation = 20);
	 
};
