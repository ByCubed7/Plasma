#pragma once

#include "../Vector.h"
#include "../Colour.h"
#include "Shader.h"
#include "OpenGL.h"

#include <iostream>

template<class T>
class Renderable
{
public:

	static void PrepareRenderer(Shader newShader);

	static void CleanUpRenderer();

	static void draw(T object, Vector2 position, Vector2Int size, Vector2 scale, Vector2 pivot, float rotate, Vector2Int crop, Colour4 color);

	Shader& getShader() 
	{
		return shader;
	}

protected:

	/// <summary>
	/// Our shader that we'll use to render
	/// </summary>
	static Shader shader;

	/// <summary>
	/// The VAO is an object which contains one or more Vertex Buffer Objects and is designed to store the information for a complete rendered object.
	/// Vertex attributes are numbered from 0 to GL_MAX_VERTEX_ATTRIBS - 1.
	/// </summary>
	static unsigned int vertexArrayObject;
	virtual void LoadRenderer() = 0;
	virtual void UnloadRenderer() = 0;

	virtual void Render(glm::vec2 position, glm::vec2 size, glm::vec2 scale, glm::vec2 pivot, float rotate, glm::vec2 crop, glm::vec3 color) = 0;
};

template <class T>
Shader Renderable<T>::shader = Shader();

template <class T>
unsigned int Renderable<T>::vertexArrayObject = 0;

template<class T>
void Renderable<T>::PrepareRenderer(Shader newShader)
{
	shader = newShader;

	// Generate a VAO for vertexArrayObject
	glGenVertexArrays(1, &vertexArrayObject);
	//std::cout << "glGenVertexArrays: " << vertexArrayObject << std::endl;

	Renderable* renderable = (Renderable*)(new T());
	renderable->LoadRenderer();
	//delete renderable;
}

template<class T>
void Renderable<T>::CleanUpRenderer()
{
	// Tell OpenGL to free up the memory used by the VAO.
	glDeleteVertexArrays(1, &vertexArrayObject);

	Renderable* renderable = (Renderable*)(new T());
	renderable->UnloadRenderer();
	//delete renderable;
}

template<class T>
void Renderable<T>::draw(T object, Vector2 position, Vector2Int size, Vector2 scale, Vector2 pivot, float rotate, Vector2Int crop, Colour4 color)
{
	//std::cout << "renderable->Render: " << vertexArrayObject << std::endl;
	Renderable* renderable = (Renderable*)&object;
	renderable->Render(
		{ position.x, position.y },
		{ size.x, size.y },
		{ scale.x, scale.y },
		{ pivot.x, pivot.y },
		rotate,
		{ crop.x, crop.y },
		{ color.r / 255.0f, color.g / 255.0f, color.b / 255.0f }
	);
}
