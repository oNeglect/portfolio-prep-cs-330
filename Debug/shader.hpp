// Lawrence Arundel CS 330 7-1 Submit Project
// if SHADER_HPP is not defined, define SHADER_HPP and produce error accordingly (IBM, 2021, p. 1)
#ifndef SHADER_HPP
#define SHADER_HPP

/// <summary>
/// function used to denote loading vertex source and fragment source code for project (Chapman, 2020, p. 1)
/// </summary>
/// <param name="vertex_file_path"></param>
/// <param name="fragment_file_path"></param>
/// <returns></returns>
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif
