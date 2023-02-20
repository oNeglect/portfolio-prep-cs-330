// Lawrence Arundel CS 330 7-1 Submit Project
#pragma once

// include file that implements the properties of the static mesh 3D class (Chapman, 2020, p. 1)
#include "common/staticMesh3D.h"

/// <summary>
/// name space that includes the properties for the static mesh 3D (Chapman, 2020, p. 1)
/// </summary>
namespace static_meshes_3D {

	/// <summary>
	/// cylinder class that inherits the static mesh 3D class to construct cylinder object within project (Chapman, 2020, p. 1)
	/// </summary>
	class Cylinder : public StaticMesh3D
	{
	public:
		Cylinder(float radius, int numSlices, float height,
			bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true);

		void render() const override;
		void renderPoints() const override;

		/// <summary>
		/// function that returns the radius of cylinder (Chapman, 2020, p. 1)
		/// </summary>
		/// <returns></returns>
		float getRadius() const;

		/// <summary>
		/// function that returns the number of slices of cylinder (Chapman, 2020, p. 1)
		/// </summary>
		/// <returns></returns>
		int getSlices() const;

		/// <summary>
		/// function that returns the height of the cylinder (Chapman, 2020, p. 1)
		/// </summary>
		/// <returns></returns>
		float getHeight() const;

		/// <summary>
		/// private variables that include the radius, number of slices, height, and the calculations for cylinder object (Chapman, 2020, p. 1)
		/// </summary>
	private:
		float _radius;
		int _numSlices;
		float _height;

		int _numVerticesSide;
		int _numVerticesTopBottom;
		int _numVerticesTotal;

		/// <summary>
		/// function that intializes the cylinder object's data points / attributes (Chapman, 2020, p. 1)
		/// </summary>
		void initializeData() override;
	};

}