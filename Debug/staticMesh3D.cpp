// Lawrence Arundel CS 330 7-1 Submit Project

//include file used to utilize functions within the static mesh 3D class (Chapman, 2020, p. 1)
#include "common/staticMesh3D.h"

// header files that are used for the glm math functions (Chapman, 2020, p. 1)
#include <glm/glm.hpp>

// namespace created for the static mesh 3D class (Chapman, 2020, p. 1)
namespace static_meshes_3D {

	// variables defined for the position attribute, texture coordinate, and normal attribute (Chapman, 2020, p. 1)
	const int StaticMesh3D::POSITION_ATTRIBUTE_INDEX = 0;
	const int StaticMesh3D::TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1;
	const int StaticMesh3D::NORMAL_ATTRIBUTE_INDEX = 2;

	/// <summary>
	/// constructor used to determine whether the mesh has the corerct position, texture coordinate, 
	/// and normals for proper implementation (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="withPositions"></param>
	/// <param name="withTextureCoordinates"></param>
	/// <param name="withNormals"></param>
	StaticMesh3D::StaticMesh3D(bool withPositions, bool withTextureCoordinates, bool withNormals)
		: _hasPositions(withPositions)
		, _hasTextureCoordinates(withTextureCoordinates)
		, _hasNormals(withNormals) {}

	/// <summary>
	/// constructor used to delete the constructor / mesh within the project (Chapman, 2020, p. 1)
	/// </summary>
	StaticMesh3D::~StaticMesh3D()
	{
		deleteMesh();
	}

	/// <summary>
	/// function used to delete the mesh within the project (Chapman, 2020, p. 1)
	/// </summary>
	void StaticMesh3D::deleteMesh()
	{
		// conditiont aht states if initialized is not true, then return null (Chapman, 2020, p. 1)
		if (!_isInitialized) {
			return;
		}

		// delete the VBO of the specified VAO and set is initialized to false (Chapman, 2020, p. 1)
		glDeleteVertexArrays(1, &_vao);
		_vbo.deleteVBO();

		_isInitialized = false;
	}

	/// <summary>
	/// function that checks whether mesh has proper positions attribute index (Chapman, 2020, p. 1)
	/// </summary>
	/// <returns></returns>
	bool StaticMesh3D::hasPositions() const
	{
		return _hasPositions;
	}

	/// <summary>
	/// function that checks whether mesh has proper texture coordinates (Chapman, 2020, p. 1)
	/// </summary>
	/// <returns></returns>
	bool StaticMesh3D::hasTextureCoordinates() const
	{
		return _hasTextureCoordinates;
	}

	/// <summary>
	/// function that checks whether mesh has proper texture coordinates (Chapman, 2020, p. 1)
	/// </summary>
	/// <returns></returns>
	bool StaticMesh3D::hasNormals() const
	{
		return _hasNormals;
	}

	/// <summary>
	/// function that checks whether mesh has proper texture coordinates (Chapman, 2020, p. 1)
	/// </summary>
	/// <returns></returns>
	int StaticMesh3D::getVertexByteSize() const
	{
		// initialize variable to zero (Chapman, 2020, p. 1)
		int result = 0;

		// conditions that state if the mesh has position or texture coordinate or normal, add proper vectors (Chapman, 2020, p. 1) 
		if (hasPositions()) {
			result += sizeof(glm::vec3);
		}

		// conditions that state if the mesh has position or texture coordinate or normal, add proper vectors (Chapman, 2020, p. 1) 
		if (hasTextureCoordinates()) {
			result += sizeof(glm::vec2);
		}

		// conditions that state if the mesh has position or texture coordinate or normal, add proper vectors (Chapman, 2020, p. 1) 
		if (hasNormals()) {
			result += sizeof(glm::vec3);
		}

		// return the vector results based on conditions (Chapman, 2020, p. 1)
		return result;
	}

	/// <summary>
	/// function that sets the vertex attribute pointers for the mesh within project (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="numVertices"></param>
	void StaticMesh3D::setVertexAttributesPointers(int numVertices)
	{
		// set variable equal to zero for offset (Chapman, 2020, p. 1)
		uint64_t offset = 0;

		// condition that states if mesh has positions or texture coordinate or normal coordinates, then enable vertex attribute array and pointer
		// for the various functions described (Chapman, 2020, p. 1)
		if (hasPositions())
		{
			glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);
			glVertexAttribPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

			offset += static_cast<unsigned long long>(sizeof(glm::vec3)) * numVertices;
		}

		// condition that states if mesh has positions or texture coordinate or normal coordinates, then enable vertex attribute array and pointer
		// for the various functions described (Chapman, 2020, p. 1)
		if (hasTextureCoordinates())
		{
			glEnableVertexAttribArray(TEXTURE_COORDINATE_ATTRIBUTE_INDEX);
			glVertexAttribPointer(TEXTURE_COORDINATE_ATTRIBUTE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(offset));

			offset += static_cast<unsigned long long>(sizeof(glm::vec2)) * numVertices;
		}

		// condition that states if mesh has positions or texture coordinate or normal coordinates, then enable vertex attribute array and pointer
		// for the various functions described (Chapman, 2020, p. 1)
		if (hasNormals())
		{
			glEnableVertexAttribArray(NORMAL_ATTRIBUTE_INDEX);
			glVertexAttribPointer(NORMAL_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

			offset += static_cast<unsigned long long>(sizeof(glm::vec3)) * numVertices;
		}
	}

}