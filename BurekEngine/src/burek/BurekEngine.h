#include <SDL\SDL.h>
#include <GL\glew.h>

namespace burek 
{


	inline int Initialize()
	{
		//initialize sdl
		SDL_Init(SDL_INIT_EVERYTHING);

		//set sdl/ogl attributes
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}
