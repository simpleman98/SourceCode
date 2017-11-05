#include "Graph.h"
#include <cmath>
namespace MyMath
{

	Graph::Graph() :_screenWidth(0), _screenHeight(0)
	{

	}


	Graph::~Graph()
	{
	}

	void Graph::init(float screenWidth, float screenHeight, MyGameEngine::Color color)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_color = color;
		_spriteBatch.init();
	}

	void Graph::drawAxes(float lineThickness)
	{
		
		_spriteBatch.draw(glm::vec4(-_screenWidth/2, -lineThickness / 2, _screenWidth, lineThickness), (GLuint)0,(float) 0, _color);
		_spriteBatch.draw(glm::vec4(- lineThickness/2, -_screenHeight/2, lineThickness, _screenHeight), (GLuint)0, (float)0, _color);
	}
	void Graph::drawCircel()
	{
		float amplitude = _screenWidth/4;
		for (float i = 0; i < 2* 3.1415f; i+= 0.01)
		{
			float x = amplitude * std::cos(i);
			float y = amplitude * std::sin(i);
			drawPoint(x, y);
		}
	}
	void Graph::startDraw()
	{
		_spriteBatch.begin();
	}
	void Graph::endDraw()
	{
		_spriteBatch.end();
		_spriteBatch.renderBatch();
	}
	void Graph::drawPoint(float x, float y)
	{
		MyGameEngine::Color blue;
		blue.r = 0;
		blue.g = 0;
		blue.b = 255;
		blue.a = 255;
		_spriteBatch.draw(glm::vec4(x,y, 2,2), (GLuint)0, (float)0,blue);


	}
}