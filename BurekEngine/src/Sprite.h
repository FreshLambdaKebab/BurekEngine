#ifndef _SPRITE_H
#define _SPRITE_H

#include <GL\glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float width, float height);
	void Draw();

private:
	int m_x, m_y;
	int m_width, m_height;

	GLuint m_vboID;
};

#endif //_SPRITE_H
