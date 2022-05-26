#pragma once

#include "Shader.h"
#include "../../Library/glad.h"

template <class T>
class Renderable
{
public:

	Renderable() {}

	static void PrepareRenderer(Shader newShader)
	{
		shader = newShader;

		// Generate a VAO for vertexArrayObject
		glGenVertexArrays(1, &vertexArrayObject);

		T* object = new T();
		Renderable* renderable = (Renderable*) object;
		renderable->LoadRenderer();
		delete object;
	}

	static void CleanUpRenderer() 
	{
		// Tell OpenGL to free up the memory used by the VAO.
		glDeleteVertexArrays(1, &vertexArrayObject);

		T* object = new T();
		Renderable* renderable = (Renderable*) object;
		renderable->UnloadRenderer();
		delete object;
	}

	static void Draw(T object, glm::vec2 position, glm::vec2 size, glm::vec2 pivot, float rotate, int frame, glm::vec3 color) 
	{
		Renderable* renderable = (Renderable*) &object;
		renderable->Render(position, size, pivot, rotate, frame, color);
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

	virtual void Render(glm::vec2 position, glm::vec2 size, glm::vec2 pivot, float rotate, int frame, glm::vec3 color) = 0;
};