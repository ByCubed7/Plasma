#pragma once

#include "Font.h"
#include "Renderer.h"
#include "Renderable.h"
#include "../Resource.h"

class Text : public Renderable<Text>
{
public:

	std::string contents;
    Font font;


protected:
    // Renderable
    void LoadRenderer() override;
    void UnloadRenderer() override;

    void Render(glm::vec2 position, glm::vec2 size, glm::vec2 scale, glm::vec2 pivot, float rotate, glm::vec2 crop, glm::vec3 color) override;
private:
    static inline unsigned int verticeVBO = 0;
};
