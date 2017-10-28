#include "Window.h"
#include "Errors.h"

namespace MyGameEngine
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BOARDERLESS)
		{
			flags |= BOARDERLESS;
		}

		// craete Window 
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			screenWidth, screenHeight, flags);
		if (_sdlWindow == nullptr)
		{
			fatalProgramError("SDL Window could not be created!");
		}

		// create Context
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
		{
			fatalProgramError("SDL_GL context could not be created!");

		}

		// init glew 
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalProgramError("Could not initialize glew!");
		}

		std::printf("**** OpenGL Version %s **** \n", glGetString(GL_VERSION));

		// Set background Color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		//SDL_GL_SetSwapInterval(1);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}