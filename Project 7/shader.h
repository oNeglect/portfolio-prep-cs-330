// Lawrence Arundel CS 330 7-1 Submit Project
// if SHADER_H is not defined, define SHADER_H and produce error accordingly (IBM, 2021, p. 1)
#ifndef SHADER_H
#define SHADER_H

// include / header file that holds all OpenGL type declarations (Chapman, 2020, p. 1)
#include <glad/glad.h>

// header files that are used for the glm math functions (Chapman, 2020, p. 1)
#include <glm/glm.hpp>

// includes that denote string and vector class for use within project (GeekforGeeks, 2022, p. 1)
#include <string>

// standard input / output stream including cin, cout, cerr, etc to utilize in project (GeeksforGeeks, 2022, p. 1)
#include <fstream>
#include <sstream>
#include <iostream>

// shader class that helps with the construction of shaders for project (Chapman, 2020, p. 1)
class Shader
{
public:

	// variable used for proper shader ID (Chapman, 2020, p. 1) 
	unsigned int ID;
	/// <summary>
	/// constructor that generates shader for project (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="vertexPath"></param>
	/// <param name="fragmentPath"></param>
	/// <param name="geometryPath"></param>
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		// retrieves the vertex soruce code and fragment source code from the specified file path (Chapman, 2020, p. 1)
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;

		// thrown exceptions in case files are not found within project (Chapman, 2020, p. 1)
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		// try/catch statement that checks to see if the proper file path can be found / opened (Chapman, 2020, p. 1)
		try
		{
			// opens the files for the vertex and fragment paths (Chapman, 2020, p. 1)
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			// read the files into the proper buffers for the vertex and fragment shader variables (Chapman, 2020, p. 1)
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// close the files after reading through buffer (Chapman, 2020, p. 1)
			vShaderFile.close();
			fShaderFile.close();

			// converts the buffer read from file into string (Chapman, 2020, p. 1)
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			// if the geometry path is also present, load into shader as well (Chapman, 2020, p. 1)
			if (geometryPath != nullptr)
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}

		// throw error if the shader file is not foudn (Chapman, 2020, p. 1)
		catch (std::ifstream::failure& e)
		{
			UNREFERENCED_PARAMETER(e);
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		// converts the buffer read from file into string (Chapman, 2020, p. 1)
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// compile the shaders required for project (Chapman, 2020, p. 1)
		unsigned int vertex, fragment;

		// vertex shader intialization (Chapman, 2020, p. 1)
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		// fragment Shader initialization (Chapman, 2020, p. 1)
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		// if the geometry path is also present, load into shader as well (Chapman, 2020, p. 1)
		unsigned int geometry;
		if (geometryPath != nullptr)
		{
			const char* gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}

		// shader program used within the project (Chapman, 2020, p. 1)
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);

		// if the geometry path is also present, attach shader (Chapman, 2020, p. 1)
		if (geometryPath != nullptr)
			glAttachShader(ID, geometry);

		// link the program to the specified ID (Chapman, 2020, p. 1)
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		// deletion of the shaders that are not in use (Chapman, 2020, p. 1)
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		// if the geometry path is also present, delete shader (Chapman, 2020, p. 1)
		if (geometryPath != nullptr)
			glDeleteShader(geometry);

	}

	/// <summary>
	/// method used to activate the shader given the proper program ID (Chapman, 2020, p. 1)
	/// </summary>
	void use()
	{
		glUseProgram(ID);
	}

	/// <summary>
	/// utility uniform functions (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	/// <summary>
	/// setter used to set the uniform location type int (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	/// <summary>
	/// setter used to set the uniform location type float (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	/// <summary>
	/// setter used to set the vector of type 2 within project with vector value (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	/// <summary>
	/// setter used to set the vector of type 2 within project with string name, float x, and float y (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	/// <summary>
	/// setter used to set the vector of type 3 within project with string name, and vec3 with
	/// passed value (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	/// <summary>
	/// setter used to set the vector of type 3 within project with string name, x, y and z variables (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	/// <summary>
	/// setter used to set the vector of type 4 within project with string name and vec4 value (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	/// <summary>
	/// setter used to set the vector of type 4 within project with string name and x, y, z, and w variables (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="w"></param>
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	/// <summary>
	/// setter used to set the matrix with string type name and mat2 (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="mat"></param>
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	/// <summary>
	///  setter used to set the matrix with string type name, and glm type mat3 (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="mat"></param>
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	/// <summary>
	/// setter used to set the matrix with string type name, and glm mat4 (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="name"></param>
	/// <param name="mat"></param>
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:

	/// <summary>
	/// linking error and compilation error reports (Chapman, 2020, p. 1)
	/// </summary>
	/// <param name="shader"></param>
	/// <param name="type"></param>
	void checkCompileErrors(GLuint shader, std::string type)
	{
		// linking error and compilation error reports (Chapman, 2020, p. 1)
		GLint success;
		GLchar infoLog[1024];

		// condition states if attempting to obtain parameter from shader object is not a success
		// then print out the compilation failed error message below, return false (Chapman, 2020, p. 1)
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);

			// condition states if attempting to obtain parameter from shader object is not a success
			// then print out the compilation failed error message below, return false (Chapman, 2020, p. 1)
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};
#endif
