#include "Library/glad.h"
#include <GLFW/glfw3.h>

#include "game.h"
#include "Resources.h"

#include <iostream>
#include "Settings.h"

// Freetype
#include <ft2build.h>]
#include FT_FREETYPE_H

FT_Library library;
FT_Face face; // handle to face object


//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Settings config;
Game App(config);

// - INPUT CALLBACKS - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	App.input.SetMousePosition(xpos, ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (!App.input.KeyExists(key)) return;
	if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

	App.input.SetKey(key, action == GLFW_PRESS);
	//if (action == GLFW_PRESS) App.input.Pressed(key);
	//else if (action == GLFW_RELEASE) App.input.Released(key);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_PRESS && action != GLFW_RELEASE) return;
	
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	App.input.SetMouseButton(button, action == GLFW_PRESS);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 





// MAIN

int main(int argc, char* argv[])
{

	// Load Freefonts
	FT_Error error = FT_Init_FreeType(&library);
	if (error) {}

	error = FT_New_Face(library, "/usr/share/fonts/truetype/arial.ttf", 0, &face);
	if (error == FT_Err_Unknown_File_Format)
	{
		// The font file could be openedand read, but it appears
		// that its font format is unsupported
	}
	else if (error)
	{
		// Another error code means that the font file could not
		// be opened or read, or that it is broken
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	std::map<char, Character> Characters;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
	
	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}

	//

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(config.screenWidth, config.screenHeight, config.name, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Load OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// CALLBACKS
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Configure OpenGL
	glViewport(0, 0, config.screenWidth, config.screenHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Init App
	App.Init();

	// deltaTime
	double deltaTime = 0.0f;
	double lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// - Update App

		// Process the User Input
		App.ProcessInput(deltaTime);

		// Update game state
		App.Update(deltaTime);

		// Check the App state to see whether to close
		if (App.state == Game::State::CLOSING) glfwSetWindowShouldClose(window, true);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		App.Render();

		glfwSwapBuffers(window);
	}

	// Clear all of the loaded resources 
	Resources::Clear();

	// Terminate the OpenGL window
	glfwTerminate();
	return 0;
}