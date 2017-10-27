#pragma once
#include <GL\glew.h>


struct Position
{
	float x;
	float y;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV {
	float u;
	float v;

};


 // The Vertex definition
struct Vertex {

	Position position;


	Color color;

	//UV texture coordinates
	UV uv; 

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void setColor(GLubyte r, GLubyte b, GLubyte g, GLubyte a)
	{
		color.r = r;
		color.b = b;
		color.g = g;
		color.a = a;
	}
	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}
};

