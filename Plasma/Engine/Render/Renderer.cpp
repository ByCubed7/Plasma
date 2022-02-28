// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Renderer.h"

namespace Render {
    Renderer::Renderer(Shader& shader)
    {
        this->shader = shader;

        // Generate a VAO for vertexArrayObject
        glGenVertexArrays(1, &vertexArrayObject);
    }

    Renderer::~Renderer()
    {
        // Tell OpenGL to free up the memory used by the VAO.
        glDeleteVertexArrays(1, &vertexArrayObject);
    }

    Shader& Renderer::GetShader()
    {
        return shader;
    }
}