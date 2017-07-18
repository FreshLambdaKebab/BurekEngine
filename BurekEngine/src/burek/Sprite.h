#ifndef _SPRITE_H
#define _SPRITE_H

#include <GL\glew.h>
#include <string>

#include "Texture.h"

namespace burek
{

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void Init(float x, float y, float width, float height, const std::string& texturePath);
		void Draw();

	private:
		float m_x, m_y;
		float m_width, m_height;

		GLuint m_vboID;

		Texture m_texture;
	};

}

#endif //_SPRITE_H
