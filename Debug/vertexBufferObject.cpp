// Lawrence Arundel CS 330 7-1 Submit Project

// standard input / output stream including cin, cout, cerr, etc to utilize in project (GeeksforGeeks, 2022, p. 1)
#include <iostream>

// includes that denote string and vector class for use within project (GeekforGeeks, 2022, p. 1)
#include <cstring>

//include file used to utilize functions within the vertex buffer object class (Chapman, 2020, p. 1)
#include "common/vertexBufferObject.h"

/// <summary>
/// function used to create the VBO for project (Chapman, 2020, p. 1)
/// </summary>
/// <param name="reserveSizeBytes"></param>
void VertexBufferObject::createVBO(size_t reserveSizeBytes)
{
	// condition that states if the buffer is created, then output that it has been created (Chapman, 2020, p. 1)
	if (_isBufferCreated)
	{
		std::cerr << "This buffer is already created! You need to delete it before re-creating it!" << std::endl;
		return;
	}

	// creation of VBO, reserves the bytes between 0 and 1024, output that the VBO is crated, and set the variable to true
	// for that specified VAO (Chapman, 2020, p. 1)
	glGenBuffers(1, &_bufferID);
	_rawData.reserve(reserveSizeBytes > 0 ? reserveSizeBytes : 1024);
	_isBufferCreated = true;
}

/// <summary>
/// function used to bind the VBO (Chapman, 2020, p. 1)
/// </summary>
/// <param name="bufferType"></param>
void VertexBufferObject::bindVBO(GLenum bufferType)
{
	// condition that states if the buffer is not created, output that the bind cannot be done (Chapman, 2020, p. 1)
	if (!_isBufferCreated)
	{
		std::cerr << "This buffer is not created yet! You cannot bind it before you create it!" << std::endl;
		return;
	}

	// set the buffer type equal to the parameter, and bind the buffer to the specified buffer ID (Chapman, 2020, p. 1)
	_bufferType = bufferType;
	glBindBuffer(_bufferType, _bufferID);
}

/// <summary>
/// function that adds data pertaining to the VBO (Chapman, 2020, p. 1)
/// </summary>
/// <param name="ptrData"></param>
/// <param name="dataSize"></param>
/// <param name="repeat"></param>
void VertexBufferObject::addRawData(const void* ptrData, size_t dataSize, int repeat)
{

	// condition that states if the required capacity is greater than the data capacity, increase the capacity and
	// set it equal to the new capacity variable. while the new capacity is less than the required capacity,
	// continue to multiple and add to the new capacity variable.
	const auto bytesToAdd = dataSize * repeat;
	const auto requiredCapacity = _bytesAdded + bytesToAdd;
	if (requiredCapacity > _rawData.capacity())
	{
		auto newCapacity = _rawData.capacity() * 2;
		while (newCapacity < requiredCapacity) {
			newCapacity *= 2;
		}

		// create the vector new raw data and reserve the capacity size with new capacity variable
		// copy the memory and move the copied data into the created vector (Chapman, 2020, p. 1)
		std::vector<unsigned char> newRawData;
		newRawData.reserve(newCapacity);
		memcpy(newRawData.data(), _rawData.data(), _bytesAdded);
		_rawData = std::move(newRawData);
	}

	// for loop that copies data and add bytes from data size (Chapman, 2020, p. 1)
	for (int i = 0; i < repeat; i++)
	{
		memcpy(_rawData.data() + _bytesAdded, ptrData, dataSize);
		_bytesAdded += dataSize;
	}
}

/// <summary>
/// function that obtains the raw data pointer within project (Chapman, 2020, p. 1)
/// </summary>
/// <returns></returns>
void* VertexBufferObject::getRawDataPointer()
{
	return _rawData.data();
}

/// <summary>
/// function that uploads the data to the gpu given the proper VBO (Chapman, 2020, p. 1)
/// </summary>
/// <param name="usageHint"></param>
void VertexBufferObject::uploadDataToGPU(GLenum usageHint)
{
	// condition that states if the buffer is not created, output that the buffer is not created yet (Chapman, 2020, p. 1) 
	if (!_isBufferCreated)
	{
		std::cerr << "This buffer is not created yet! Call createVBO before uploading data to GPU!" << std::endl;
		return;
	}

	// buffer the required data, upload data variable set equal to true, add bytes to the uploaded data size, and set bytes added 
	// equal to zero (Chapman, 2020, p. 1)


	glBufferData(_bufferType, _bytesAdded, _rawData.data(), usageHint);
	_isDataUploaded = true;
	_uploadedDataSize = _bytesAdded;
	_bytesAdded = 0;
}

/// <summary>
/// function used to map the buffer to memory given parameter (Chapman, 2020, p. 1)
/// </summary>
/// <param name="usageHint"></param>
/// <returns></returns>
void* VertexBufferObject::mapBufferToMemory(GLenum usageHint) const
{
	// if data uploaded is not true, then return a null ptr (Chapman, 2020, p. 1)
	if (!_isDataUploaded) {
		return nullptr;
	}

	// return the map buffer with the parameter and specified buffer type (Chapman, 2020, p. 1)
	return glMapBuffer(_bufferType, usageHint);
}

/// <summary>
/// function that maps the sub buffer to memeory given the parameters (Chapman, 2020, p. 1)
/// </summary>
/// <param name="usageHint"></param>
/// <param name="offset"></param>
/// <param name="length"></param>
/// <returns></returns>
void* VertexBufferObject::mapSubBufferToMemory(GLenum usageHint, size_t offset, size_t length) const
{
	// if data uploaded is not true, then return a null ptr (Chapman, 2020, p. 1)
	if (!_isDataUploaded) {
		return nullptr;
	}

	// return the map buffer with the parameter and specified buffer type (Chapman, 2020, p. 1)
	return glMapBufferRange(_bufferType, offset, length, usageHint);
}

/// <summary>
/// function that unmaps the buffer (Chapman, 2020, p. 1)
/// </summary>
void VertexBufferObject::unmapBuffer() const
{
	glUnmapBuffer(_bufferType);
}

/// <summary>
/// function that obtains the buffer ID within project (Chapman, 2020, p. 1)
/// </summary>
/// <returns></returns>
GLuint VertexBufferObject::getBufferID() const
{
	return _bufferID;
}

/// <summary>
/// function that mapes the buffer to memory given the parameter (Chapman, 2020, p. 1)
/// </summary>
/// <param name="usageHint"></param>
/// <returns></returns>
void* VertexBufferObject::mapBufferToMemory(GLenum usageHint)
{
	return nullptr;
}

/// <summary>
/// function that maps the sub buffer to memory given the parameters (Chapman, 2020, p. 1)
/// </summary>
/// <param name="usageHint"></param>
/// <param name="offset"></param>
/// <param name="length"></param>
/// <returns></returns>
void* VertexBufferObject::mapSubBufferToMemory(GLenum usageHint, uint32_t offset, uint32_t length)
{
	return nullptr;
}

/// <summary>
/// function that unmaps the buffer within project (Chapman, 2020, p. 1)
/// </summary>
void VertexBufferObject::unmapBuffer()
{
}

/// <summary>
/// function that obtains the buffer ID (Chapman, 2020, p. 1)
/// </summary>
/// <returns></returns>
GLuint VertexBufferObject::getBufferID()
{
	return GLuint();
}

/// <summary>
/// function that returns the buffer size (Chapman, 2020, p. 1)
/// </summary>
/// <returns></returns>
uint32_t VertexBufferObject::getBufferSize()
{
	return _isDataUploaded ? _uploadedDataSize : _bytesAdded;
}

/// <summary>
/// function that deletes the VBO (Chapman, 2020, p. 1)
/// </summary>
void VertexBufferObject::deleteVBO()
{
	// if the buffer is created, return statement (Chapman, 2020, p. 1)
	if (!_isBufferCreated) {
		return;
	}

	// output deleteing the vertex buffer object and set the data uploaded and buffer created variables to false (Chapman, 2020, p. 1)
	glDeleteBuffers(1, &_bufferID);
	_isDataUploaded = false;
	_isBufferCreated = false;
}
