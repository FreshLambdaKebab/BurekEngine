#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL\glew.h>

namespace burek
{

	struct Texture
	{
		GLuint ID;
		int width;
		int height;
	};

}

#endif //_TEXTURE_H
