#ifndef _VERTEX_BUFFER_H
#define _VERTEX_BUFFER_H

namespace burek
{

	struct Position
	{
		float x;
		float y;
	};

	struct Color
	{
		Color() :r(0), g(0), b(0), a(a) {}
		Color(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) :r(red), g(green), b(blue), a(alpha) {}

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		Position position;
		Color color;
		UV uv;

		//functions for ease
		void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void SetUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}

		void SetPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

	};

}

#endif
