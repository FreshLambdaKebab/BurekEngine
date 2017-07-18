#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

namespace burek
{

	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int CreateWindow(const std::string& name, int screenWidth, int screenHeight, unsigned int currentFlags);
		void SwapBuffers();

		int GetScreenWidth()const { return m_screenWidth; }
		int getScreenHeight()const { return m_screenHeight; }

	private:
		SDL_Window* m_window;
		int m_screenWidth, m_screenHeight;
	};

}

#endif //_WINDOW_H
