#pragma once

#include "Sprite.h"
#include "Vertex.h"
#include "SpriteBatch.h"
#include <glm\glm.hpp>
namespace MyMath
{
	class Graph
	{
	public:
		Graph();
		~Graph();

		void init(float screenWidth, float screenHeight, MyGameEngine::Color color);
		void drawAxes(float lineThickness);
		void drawCircel();
		void startDraw();
		void endDraw();

	private:
		float _screenWidth;
		float _screenHeight;
		MyGameEngine::Color _color;
		MyGameEngine::SpriteBatch _spriteBatch;
		void drawPoint(float x, float y);

	};
}

