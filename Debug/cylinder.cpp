// Lawrence Arundel CS 330 7-1 Submit Project

// utilizes vector functions with vector library (Chapman, 2020, p. 1)
#include <vector>

// header files that are used for the glm math functions (Chapman, 2020, p. 1)
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// include file that contains the properties of the cylinder header file (Chapman, 2020, p. 1)
#include "cylinder.h"

/// <summary>
/// name space that includes the properties for the static mesh 3D (Chapman, 2020, p. 1)
/// </summary>
namespace static_meshes_3D {

	/// <summary>
	/// constructor of the cylinder class given the various parameters for the construction of the object (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="radius"></param>
	/// <param name="numSlices"></param>
	/// <param name="height"></param>
	/// <param name="withPositions"></param>
	/// <param name="withTextureCoordinates"></param>
	/// <param name="withNormals"></param>
	Cylinder::Cylinder(float radius, int numSlices, float height, bool withPositions, bool withTextureCoordinates, bool withNormals)
		: StaticMesh3D(withPositions, withTextureCoordinates, withNormals)
		, _radius(radius)
		, _numSlices(numSlices)
		, _height(height)
	{
		initializeData();
	}

	/// <summary>
	/// function that returns the radius attribute for the cylinder object (Chapman, 2020, p. 1)
	/// </summary>
	/// <returns></returns>
	float Cylinder::getRadius() const
	{
		return _radius;
	}

	/// <summary>
	/// function that returns the number of slices within the cylinder object (Chapman, 2020, p. 1)
	/// </summary>
	/// <returns></returns>
	int Cylinder::getSlices() const
	{
		return _numSlices;
	}

	/// <summary>
	/// function that returns the height of the cylinder object (Chapman, 2020, p. 1)
	/// </summary>
	/// <returns></returns>
	float Cylinder::getHeight() const
	{
		return _height;
	}

	/// <summary>
	/// function that initializes the data for the cylinder object (Chapman, 2020, p. 1)
	/// </summary>
	void Cylinder::initializeData()
	{
		// condition that states if the object is alread intialized, return null (Chapman, 2020, p. 1)
		if (_isInitialized) {
			return;
		}

		// calculates the number of vertices for the side, bottom, and combines into the total number (Chapman, 2020, p. 1)
		_numVerticesSide = (_numSlices + 1) * 2;
		_numVerticesTopBottom = _numSlices + 2;
		_numVerticesTotal = _numVerticesSide + _numVerticesTopBottom * 2;

		// generates the VAO and VBO of the cylinder object (Chapman, 2020, p. 1)
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		_vbo.createVBO(getVertexByteSize() * _numVerticesTotal);

		// calculates the sines and cosines of the cylinder object given correct parameters (Chapman, 2020, p. 1)
		const auto sliceAngleStep = 2.0f * glm::pi<float>() / float(_numSlices);
		auto currentSliceAngle = 0.0f;
		std::vector<float> sines, cosines;
		for (auto i = 0; i <= _numSlices; i++)
		{
			sines.push_back(sin(currentSliceAngle));
			cosines.push_back(cos(currentSliceAngle));

			currentSliceAngle += sliceAngleStep;
		}

		// condition that states if the object has vertex positions, then calculate the x and z coodinates for cylinder object
		// add the side vertices, top, and bottom vertices for construction (Chapman, 2020, p. 1)
		if (hasPositions())
		{
			// Pre-calculate X and Z coordinates
			std::vector<float> x;
			std::vector<float> z;
			for (auto i = 0; i <= _numSlices; i++)
			{
				x.push_back(cosines[i] * _radius);
				z.push_back(sines[i] * _radius);
			}

			// for loop that constructs the side vertices of the cylinder object (Chapman, 2020, p. 1)
			for (auto i = 0; i <= _numSlices; i++)
			{
				const auto topPosition = glm::vec3(x[i], _height / 2.0f, z[i]);
				const auto bottomPosition = glm::vec3(x[i], -_height / 2.0f, z[i]);
				_vbo.addRawData(&topPosition, sizeof(glm::vec3));
				_vbo.addRawData(&bottomPosition, sizeof(glm::vec3));
			}

			// function that creates the top cover of the cylinder (Chapman, 2020, p. 1)
			glm::vec3 topCenterPosition(0.0f, _height / 2.0f, 0.0f);
			_vbo.addRawData(&topCenterPosition, sizeof(glm::vec3));
			for (auto i = 0; i <= _numSlices; i++)
			{
				const auto topPosition = glm::vec3(x[i], _height / 2.0f, z[i]);
				_vbo.addRawData(&topPosition, sizeof(glm::vec3));
			}

			// function that creates the bottom cover of the cylinder (Chapman, 2020, p. 1)
			glm::vec3 bottomCenterPosition(0.0f, -_height / 2.0f, 0.0f);
			_vbo.addRawData(&bottomCenterPosition, sizeof(glm::vec3));
			for (auto i = 0; i <= _numSlices; i++)
			{
				const auto bottomPosition = glm::vec3(x[i], -_height / 2.0f, -z[i]);
				_vbo.addRawData(&bottomPosition, sizeof(glm::vec3));
			}
		}

		// condition that states if the object has texture coordinates, then calculate the texture coordinates for the object
		// and implement (Chapman, 2020, p. 1)
		if (hasTextureCoordinates())
		{
			// mapping of the texture coordinates twice around the cylinder object (Chapman, 2020, p. 1)
			const auto sliceTextureStepU = 2.0f / float(_numSlices);

			auto currentSliceTexCoordU = 0.0f;
			for (auto i = 0; i <= _numSlices; i++)
			{
				_vbo.addData(glm::vec2(currentSliceTexCoordU, 1.0f));
				_vbo.addData(glm::vec2(currentSliceTexCoordU, 0.0f));

				// executes updates for each slice in the cylinder object (Chapman, 2020, p. 1)
				currentSliceTexCoordU += sliceTextureStepU;
			}

			// top cover texture coordinate positions (Chapman, 2020, p. 1)
			glm::vec2 topBottomCenterTexCoord(0.5f, 0.5f);
			_vbo.addData(topBottomCenterTexCoord);
			for (auto i = 0; i <= _numSlices; i++) {
				_vbo.addData(glm::vec2(topBottomCenterTexCoord.x + sines[i] * 0.5f, topBottomCenterTexCoord.y + cosines[i] * 0.5f));
			}

			// bottom cover texture coordinate positions (Chapman, 2020, p. 1)
			_vbo.addData(topBottomCenterTexCoord);
			for (auto i = 0; i <= _numSlices; i++) {
				_vbo.addData(glm::vec2(topBottomCenterTexCoord.x + sines[i] * 0.5f, topBottomCenterTexCoord.y - cosines[i] * 0.5f));
			}
		}

		// condition that states if the object has normals, then construct normals for the cylinder object (Chapman, 2020, p. 1)
		if (hasNormals())
		{
			for (auto i = 0; i <= _numSlices; i++) {
				_vbo.addData(glm::vec3(cosines[i], 0.0f, sines[i]), 2);
			}

			// adds normal coordinates for the top cover of cylinder (Chapman, 2020, p. 1)
			_vbo.addData(glm::vec3(0.0f, 1.0f, 0.0f), _numVerticesTopBottom);

			// adds normal coordinates for the bottom cover of cylinder (Chapman, 2020, p. 1)
			_vbo.addData(glm::vec3(0.0f, -1.0f, 0.0f), _numVerticesTopBottom);
		}

		// upload all data to the GPU (Chapman, 2020, p. 1)
		_vbo.bindVBO();
		_vbo.uploadDataToGPU(GL_STATIC_DRAW);
		setVertexAttributesPointers(_numVerticesTotal);

		// set is initialized to true (Chapman, 2020, p. 1)
		_isInitialized = true;
	}

	/// <summary>
	/// function that renders the cylinder object (Chapman, 2020, p. 1)
	/// </summary>
	void Cylinder::render() const
	{
		// condition that states if is initialized is true, then retun null (Chapman, 2020, p. 1)
		if (!_isInitialized) {
			return;
		}

		// generation of various vao used within the program / binding properties (Chapman, 2020, p. 1)
		glBindVertexArray(_vao);

		// function used to draw the element of the cylinder given the correct properties (Chapman, 2020, p. 1)
		glDrawArrays(GL_TRIANGLE_STRIP, 0, _numVerticesSide);

		// function used to draw the element of the cylinder given the correct properties (Chapman, 2020, p. 1)
		glDrawArrays(GL_TRIANGLE_FAN, _numVerticesSide, _numVerticesTopBottom);

		// function used to draw the element of the cylinder given the correct properties (Chapman, 2020, p. 1)
		glDrawArrays(GL_TRIANGLE_FAN, _numVerticesSide + _numVerticesTopBottom, _numVerticesTopBottom);
	}

	/// <summary>
	/// function that renders the points for the cylinder object (Chapman, 2020, p. 1)
	/// </summary>
	void Cylinder::renderPoints() const
	{
		// condition that states if is initialized is true, then retun null (Chapman, 2020, p. 1)
		if (!_isInitialized) {
			return;
		}

		// generation of various vao used within the program / binding properties (Chapman, 2020, p. 1)
		glBindVertexArray(_vao);

		// function used to draw the element of the cylinder given the correct properties (Chapman, 2020, p. 1)
		glDrawArrays(GL_POINTS, 0, _numVerticesTotal);
	}

}