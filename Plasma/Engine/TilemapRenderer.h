#pragma once

#include "../Library/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Tilemap.h"
#include "shader.h"


class TilemapRenderer
{
public:
    // Constructor (inits shaders/shapes)
    TilemapRenderer(Shader& shader);

    // Destructor
    ~TilemapRenderer();

    // Renders a defined quad textured with given sprite
    void DrawTilemap(glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, int frame = 0, glm::vec3 color = glm::vec3(1.0f));
    
    void Bind(Tilemap* tilemap);
    
private:
    // Render state
    Shader shader;
    unsigned int quadVAO;

    Tilemap* tilemap;

    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};
