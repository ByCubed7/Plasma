#pragma once

#include "../Vector.h"
#include "Shader.h"
#include "glad.h"

#include <iostream>

template<class T>
class Renderable
{
public:

	static void PrepareRenderer(Shader newShader)
	{
		shader = newShader;

		// Generate a VAO for vertexArrayObject
		glGenVertexArrays(1, &vertexArrayObject);
		//std::cout << "glGenVertexArrays: " << vertexArrayObject << std::endl;

		Renderable* renderable = (Renderable*)(new T());
		renderable->LoadRenderer();
		//delete renderable;
	}

	static void CleanUpRenderer() 
	{
		// Tell OpenGL to free up the memory used by the VAO.
		glDeleteVertexArrays(1, &vertexArrayObject);

		Renderable* renderable = (Renderable*)(new T());
		renderable->UnloadRenderer();
		//delete renderable;
	}

	static void Draw(T object, Vector2 position, Vector2UInt size, Vector2 scale, Vector2 pivot, float rotate, Vector2Int crop, RGBA color)
	{
		//std::cout << "renderable->Render: " << vertexArrayObject << std::endl;
		Renderable* renderable = (Renderable*) &object;
		renderable->Render(
			{ position.x, position.y }, 
			{ size.x, size.y }, 
			{ scale.x, scale.y }, 
			{ pivot.x, pivot.y }, 
			rotate, 
			{ crop.x, crop.y }, 
			{ color.x / 255.0f, color.y / 255.0f, color.z / 255.0f }
		);
	}

	Shader& GetShader() 
	{
		return shader;
	}

protected:

	/// <summary>
	/// Our shader that we'll use to render
	/// </summary>
	static inline Shader shader = Shader();

	/// <summary>
	/// The VAO is an object which contains one or more Vertex Buffer Objects and is designed to store the information for a complete rendered object.
	/// Vertex attributes are numbered from 0 to GL_MAX_VERTEX_ATTRIBS - 1.
	/// </summary>
	static inline unsigned int vertexArrayObject = 0;
	virtual void LoadRenderer() = 0;
	virtual void UnloadRenderer() = 0;

	virtual void Render(glm::vec2 position, glm::vec2 size, glm::vec2 scale, glm::vec2 pivot, float rotate, glm::vec2 crop, glm::vec3 color) = 0;
};