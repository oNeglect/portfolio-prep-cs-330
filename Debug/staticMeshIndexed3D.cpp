// Lawrence Arundel CS 330 7-1 Submit Project

//include file used to utilize functions within the static mesh 3D indexed class (Chapman, 2020, p. 1)
#include "common/staticMeshIndexed3D.h"

// namespace created for the static mesh 3D indexed class (Chapman, 2020, p. 1)
namespace static_meshes_3D {

	/// <summary>
	/// constructor used to determine where the vertex positions, texture coordinates, and normals are used within project (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="withPositions"></param>
	/// <param name="withTextureCoordinates"></param>
	/// <param name="withNormals"></param>
	StaticMeshIndexed3D::StaticMeshIndexed3D(bool withPositions, bool withTextureCoordinates, bool withNormals)
		: StaticMesh3D(withPositions, withTextureCoordinates, withNormals) {}

	/// <summary>
	///  function used to describe the static mesh index 3d class that deconstructs the VBO for VAO described (Chapman, 2020, p. 1)
	/// </summary>
	StaticMeshIndexed3D::~StaticMeshIndexed3D()
	{
		// condition that states if VAO is initialized, then delete the VBO for that specified VAO (Chapman, 2020, p. 1)
		if (_isInitialized) {
			_indicesVBO.deleteVBO();
		}
	}

	/// <summary>
	/// function used to delete the mesh if it is initialized (Chapman, 2020, p. 1)
	/// </summary>
	void StaticMeshIndexed3D::deleteMesh()
	{
		// condition that states if the VAO is initialized, then delete the VBO for that specified VAO (Chapman, 2020, p. 1)
		if (_isInitialized) {
			_indicesVBO.deleteVBO();
			StaticMesh3D::deleteMesh();
		}
	}

}