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


 // The Vertex definition
struct Vertex {

	Position position;
	Color color;
};