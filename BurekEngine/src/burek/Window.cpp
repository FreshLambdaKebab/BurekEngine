#include "Window.h"
#include "Debug.h"

namespace burek
{

	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	int Window::CreateWindow(const std::string & name, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (currentFlags & SDL_WINDOW_FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (currentFlags & SDL_WINDOW_BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		//create an sdl window
		m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth,
			screenHeight, flags);

		if (m_window == nullptr)
		{
			FatalError("SDL window could not be created");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
		if (glContext == nullptr)
		{
			FatalError("SDL_GLContext could not be created");
		}

		//initialize glew
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			FatalError("could not initialize glew");
		}

		//check and print ogl version
		printf("**** OpenGL Version: %s ****\n", glGetString(GL_VERSION));

		//set background color to desired color
		glClearColor(0.2f, 0.3f, 0.9f, 1.0f);

		//set vsync
		SDL_GL_SetSwapInterval(1);

		return 0;
	}

	void Window::SwapBuffers()
	{
		//swap buffers
		SDL_GL_SwapWindow(m_window);
	}

}
