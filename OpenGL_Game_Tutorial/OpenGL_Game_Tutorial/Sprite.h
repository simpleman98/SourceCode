#pragma once

#include <GL\glew.h>

class Sprite
{
public:
	Sprite(); // default constructor
	Sprite(float screenWidth, float screenHeight);
	
	~Sprite();

	void init(float x, float y, float width, float height);

	void draw();
	void initNormalized(float x, float y, float width, float height);

private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID;
	float _screenWidth;
	float _screenHeight;
};

