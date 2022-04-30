// By @ByCubed7 on Twitter

#include "All.h" 
//#define VERBOSE

#include "App.h"
#include "Window.h"
#include "../Library/OpenAL/AL/al.h"

#include <chrono>
#include <thread>

namespace Engine {
	App* App::instance = nullptr;

	App::App()
	{
		instance = this;
		window = nullptr;
		scene = nullptr;

		size = Vector2(100);
	}


	Engine::Scene* App::CreateGame()
	{
		Engine::Scene* newScene = new Engine::Scene(this);
		// Add scene to list
		return newScene;
	}

	int App::Build(Engine::Scene* setScene)
	{
		scene = setScene;

		glfwInit();

		// The only OpenGL 3.x and 4.x contexts currently supported by macOS are forward-compatible, 
		// core profile contexts. The supported versions are 3.2 on 10.7 Lion and 3.3 and 4.1 on 10.9 Mavericks. 
		// In all cases, your GPU needs to support the specified OpenGL version for context creation to succeed.

		// Specify the client API version that the created context must be compatible with. 
		// The exact behavior of these hints depend on the requested client API.
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Was 3
		
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		// Specifies which OpenGL profile to create the context for
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = new Window(this);

		// Load OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		auto callbackException = [](GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
		{ App::instance->GraphicsCallbackException(source, type, id, severity, length, message, userParam); };


		// Configure OpenGL
		glViewport(0, 0, size.x, size.y);
		glEnable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Debugging Callback
		int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(callbackException, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}


		return 0;
	}

	int App::Run(Engine::Scene* setScene)
	{
		window->LoadScene(scene);

		SetSize(window->GetMonitorSize());

		// Delta Time
		double deltaTime = 0.0f;
		double lastFrame = 0.0f;

		int targetFrameRate = 30;

		while (window->state == Window::State::RUNNING)
		{
			// Calculate delta time
			double currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			
			// Get framerate
			double wait_time = 1.0 / targetFrameRate;
			double dur = wait_time - deltaTime;

			if (dur > 0) {
				std::this_thread::sleep_for(std::chrono::duration<double>(dur));
			}

			//std::cout << "Framerate: " << 1 / dur << std::endl;
			
			glfwPollEvents();

			// Process the User Input
			scene->ProcessInput(deltaTime);

			// Update game state
			scene->Update(deltaTime);

			window->Render();
			 
			// Clear render
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
	
			//* Print any errors
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR)
				std::cout << "[MAINLOOP] OpenGL Error: " << err << std::endl;
		}

		//delete audio;

		// Clear all of the loaded resources 
		
		Texture2D::CleanUp();
		Shader::CleanUp();
		Font::CleanUp();

		// Terminate the OpenGL window
		glfwTerminate();

		return 0;
	}

	Engine::Window* App::GetWindow()
	{
		return window;
	}

	Engine::Scene* App::GetScene()
	{
		return scene;
	}

	Vector2 App::GetSize()
	{
		return size;
	}

	void App::SetSize(Vector2 newSize)
	{
		size = newSize;
		
		// Update the scenes projection matrix
		scene->UpdateProjection();

		// Update the windows size
		window->UpdateSize();

		glViewport(0, 0, size.x, size.y);
	}

	// -- Callbacks
	void App::GraphicsCallbackException(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
	{
		// Ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		std::cout << "---------------" << std::endl;
		std::cout << "Debug message (" << id << "): " << message << std::endl;

		switch (source)
		{
			case GL_DEBUG_SOURCE_API:				std::cout << "Source: API"; break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		std::cout << "Source: Window System"; break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER:	std::cout << "Source: Shader Compiler"; break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:		std::cout << "Source: Third Party"; break;
			case GL_DEBUG_SOURCE_APPLICATION:		std::cout << "Source: Application"; break;
			case GL_DEBUG_SOURCE_OTHER:				std::cout << "Source: Other"; break;
		} std::cout << std::endl;

		switch (type)
		{
			case GL_DEBUG_TYPE_ERROR:				std::cout << "Type: Error"; break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	std::cout << "Type: Deprecated Behaviour"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	std::cout << "Type: Undefined Behaviour"; break;
			case GL_DEBUG_TYPE_PORTABILITY:			std::cout << "Type: Portability"; break;
			case GL_DEBUG_TYPE_PERFORMANCE:			std::cout << "Type: Performance"; break;
			case GL_DEBUG_TYPE_MARKER:				std::cout << "Type: Marker"; break;
			case GL_DEBUG_TYPE_PUSH_GROUP:			std::cout << "Type: Push Group"; break;
			case GL_DEBUG_TYPE_POP_GROUP:			std::cout << "Type: Pop Group"; break;
			case GL_DEBUG_TYPE_OTHER:				std::cout << "Type: Other"; break;
		} std::cout << std::endl;

		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:			std::cout << "Severity: high"; break;
			case GL_DEBUG_SEVERITY_MEDIUM:			std::cout << "Severity: medium"; break;
			case GL_DEBUG_SEVERITY_LOW:				std::cout << "Severity: low"; break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:	std::cout << "Severity: notification"; break;
		} std::cout << std::endl;
		std::cout << std::endl;
	}


}
