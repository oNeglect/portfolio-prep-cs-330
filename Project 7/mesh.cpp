// Lawrence Arundel CS 330 7-1 Submit Project 

// if mesh_h is not defined, define mesh_h and produce error accordingly (IBM, 2021, p. 1)
#ifndef MESH_H
#define MESH_H

// include / header file that holds all OpenGL type declarations (Chapman, 2020, p. 1)
#include <glad/glad.h> 

// header files that are used for the glm math functions (Chapman, 2020, p. 1)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// header file that includes the properties for the shader class (Chapman, 2020, p. 1)
#include "shader.h"

// includes that denote string and vector class for use within project (GeekforGeeks, 2022, p. 1)
#include <string>
#include <vector>

// namespace std that is used for various functions throughout the project (Chapman, 2020, p. 1)
using namespace std;

// structure used to denote the vertex class position, normalized coordinates, texture coordinates, tangent vector,
// and bit tangent vector (Chapman, 2020, p. 1)
struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

// structure used to determine the texture object with properties id, type, and path (Chapman, 2020, p. 1)
struct Texture {
	unsigned int id;
	string type;
	string path;
};

// creation of mesh used to construct VAO and VBO (Chapman, 2020, p. 1)
class Mesh {
public:
	// proper mesh data used to determine the vector for verticies, indices, and textures, while denoted the VAO for mesh (Chapman, 2020, p. 1)
	vector<Vertex>       vertices;
	vector<unsigned int> indices;
	vector<Texture>      textures;
	unsigned int VAO;

	/// <summary>
	/// // proper constructor used in the creation of the mesh (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="vertices"></param>
	/// <param name="indices"></param>
	/// <param name="textures"></param>
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		// function used to set the vertex buffers and its attribute pointers for the creation of mesh (Chapman, 2020, p. 1)
		setupMesh();
	}

	/// <summary>
	/// // method used to render the mesh (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="shader"></param>
	void Draw(Shader& shader)
	{
		// assign the proper diffuse, specular, normal, and height variables and draw / create appropriate textures (Chapman, 2020, p. 1)
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;

		// for loop that determins the size and texture type while binding the units  by texture number (Chapman, 2020, p. 1)
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			// bind textures on corresponding texture units (Chapman, 2020, p. 1)
			glActiveTexture(GL_TEXTURE0 + i);
			// variables used to retrieve the texture number (Chapman, 2020, p. 1)
			string number;
			string name = textures[i].type;

			// condition that states if the name equals texture_diffuse, number equals the iterative version of diffuseNr 
			// else if the name equals texture_specular, set number equal to iterative version of specularNr
			// else if name equals texture_normal, set number equal to iterative version of normalNr
			// else if name equals texture_height, set number equal to iterative version of heightNr (Chapman, 2020, p. 1)
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);

			// set the sampler to the correct texture unit (Chapman, 2020, p. 1)
			glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);

			// bind textures on corresponding texture units (Chapman, 2020, p. 1)
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		// activation of VBOs that lie within the mesh's VAO (Chapman, 2020, p. 1)
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// bind textures on corresponding texture units (Chapman, 2020, p. 1)
		glActiveTexture(GL_TEXTURE0);
	}

private:
	// rendering variables used within the creation of mesh (Chapman, 2020, p. 1)
	unsigned int VBO, EBO;

	/// <summary>
	/// // creation and setup of the mesh within the project (Chapman, 2020, p. 1)
	/// </summary>
	void setupMesh()
	{
		// generation of various vao used within the program / binding properties (Chapman, 2020, p. 1)
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// activation of VBOs that lie within the mesh's VAO (Chapman, 2020, p. 1)
		glBindVertexArray(VAO);

		// creation of VBO (Chapman, 2020, p. 1)
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// vertex attribute pointers - vertex coordinates (Chapman, 2020, p. 1)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// vertex attribute pointers - normalized coordinates (Chapman, 2020, p. 1)
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		// vertex attribute pointers - texture coordinates (Chapman, 2020, p. 1)
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		// vertex attribute pointers - tangent (Chapman, 2020, p. 1)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

		// vertex attribute pointers - bitangent (Chapman, 2020, p. 1)
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

		// generation of various vao used within the program / binding properties (Chapman, 2020, p. 1)
		glBindVertexArray(0);
	}
};
#endif
