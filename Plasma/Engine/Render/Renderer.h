// By @ByCubed7 on Twitter

#pragma once

#include "Shader.h"

namespace Render
{
	/// <summary>
	/// Tells openGl how to render a specific object
	/// </summary>
	class Renderer
	{
	public:
		/// <summary>
		/// The default constructor.
		/// Initialise the renderer, generate the VAO and buffers, as well as anything else required when initialising.
		/// </summary>
		/// <param name="shader">: The shader the tenderer will use</param>
		Renderer(Shader& shader);

		// Deconstructor
		~Renderer();

		Shader& getShader();

		static const int PPU = 16;

	protected:
		/// <summary>
		/// Our shader that we'll use to render
		/// </summary>
		Shader shader;

		/// <summary>
		/// The VAO is an object which contains one or more Vertex Buffer Objects and is designed to store the information for a complete rendered object.
		/// Vertex attributes are numbered from 0 to GL_MAX_VERTEX_ATTRIBS - 1.
		/// </summary>
		unsigned int vertexArrayObject;
	};
}