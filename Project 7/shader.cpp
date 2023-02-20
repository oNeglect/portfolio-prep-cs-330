// Lawrence Arundel CS 330 7-1 Submit Project

// standard input / output stream including cin, cout, cerr, etc to utilize in project (GeeksforGeeks, 2022, p. 1)
#include <stdio.h> 

// includes that denote string and vector class for use within project (GeekforGeeks, 2022, p. 1)
#include <string>

// utilizes vector functions with vector library (Chapman, 2020, p. 1)
#include <vector>

 // standard input / output stream including cin, cout, cerr, etc to utilize in project (GeeksforGeeks, 2022, p. 1)
#include <iostream>

 // standard input / output stream including cin, cout, cerr, etc to utilize in project (GeeksforGeeks, 2022, p. 1)
#include <fstream>

// library used to denote sorting, searching, counting, and manipulating of data within project (cppreference, 2022, p. 1)
#include <algorithm>

// stringstream associates a string object with a stream allowing you to read from the string as if it were a stream (geeksforgeeks, 2022, p. 1)
#include <sstream>

// namespace std that is used for various functions throughout the project (Chapman, 2020, p. 1)
using namespace std;

// standard library header file for C++ defining functions and macros to facilitate stadardized and efficient code across teams and platforms (Exterman, 2021, p. 1)
#include <stdlib.h>

// includes that denote string within the project (GeekforGeeks, 2022, p. 1)
#include <string.h>

// include for glew.h header file which defines macros that disable any OpenGL header that the GLFW header includes (GLFW, 2018, p. 1)
#include <GL/glew.h>

// include file that denotes the shader.hpp files contents within project / loading of shaders (Chapman, 2020, p. 1)
#include "shader.hpp"

/// <summary>
/// class used to load shaders given the vertex and fragment file paths references (Chapman, 2020, p. 1)
/// </summary>
/// <param name="vertex_file_path"></param>
/// <param name="fragment_file_path"></param>
/// <returns></returns>
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	// varibles used to crate the shaders used within project (Chapman, 2020, p. 1)
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// executable code that reads the vertex shader code from the specified file (Chapman, 2020, p. 1)
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

	// condition that states of the vertex shader stream variable is open, then read from the file and load into buffer
	// finally set vertex shader code equal to the string per line, and close the file after reading
	// else output that the file does not exist (Chapman, 2020, p. 1)
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		return 0;
	}

	// executable code that reads the fragment shader code from the specified file (Chapman, 2020, p. 1)
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);

	// condition that states of the vertex shader stream variable is open, then read from the file and load into buffer
	// finally set vertex shader code equal to the string per line, and close the file after reading
	// else output that the file does not exist (Chapman, 2020, p. 1)
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	// set glint variable result equal to false and create infologlength for compilation purposes (Chapman, 2020, p. 1)
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// compilation of the vertex shader code (Chapman, 2020, p. 1)
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// checking of the vertex shader code (Chapman, 2020, p. 1)
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	// if the infologlength is greater than zero, print out error message that the vertex shader code does not exist / non-implemented (Chapman, 2020, p. 1)
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// compilation of the fragment shader code (Chapman, 2020, p. 1)
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// checking of the fragment shader code (Chapman, 2020, p. 1)
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	// if the infologlength is greater than zero, print out error message that the fragment shader code does not exist / non-implemented (Chapman, 2020, p. 1)
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// linking of program (Chapman, 2020, p. 1)
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// checking of the program linked (Chapman, 2020, p. 1)
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	// if the infologlength is greater than zero, print out error message that the program does not exist / non-implemented (Chapman, 2020, p. 1)
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	// detach the vertex and fragment shader from program ID (Chapman, 2020, p. 1)
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	// delete the vertex and fragment shader ID (Chapman, 2020, p. 1)
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	// returns the program ID (Chapman, 2020, p. 1)
	return ProgramID;
}


