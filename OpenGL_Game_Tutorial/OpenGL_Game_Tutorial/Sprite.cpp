#include "Sprite.h"
#include "Vertex.h"
#include <cstdlib>

Sprite::Sprite(float screenWidth, float screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_vboID = 0;
}

Sprite::Sprite()
{
	
	_vboID = 0;
}

Sprite::~Sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	//First Triangle 
	
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(x , y + height);
	vertexData[1].setUV(0.0f, 1.0f);
	

	vertexData[2].setPosition(x, y );
	vertexData[2].setUV(0.0f, 0.0f);
	

	//SecondTriangle
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(x + width, y );
	vertexData[4].setUV(1.0f, 0.0f);


	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 255, 255);
	}


	/*vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);
*/


	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);





}

void Sprite::draw()
{

	// bind the buffer objects
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	//Tell opengl that we want to use the first 
	//attribute array.
	glEnableVertexAttribArray(0); // 0 index 

	// Position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// Color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//This is  the UV attrivute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::initNormalized(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	float xbinary =(x / (_screenWidth/2)) -1.0f;
	float ybinary = (y / (_screenHeight /2)) -1.0f;

	float widthbinary = (width / (_screenWidth /2));
	float heightbinary = (height / (_screenWidth /2));


	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	//First Triangle 
	
	vertexData[0].setPosition(xbinary + widthbinary, ybinary + heightbinary);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(xbinary, ybinary + heightbinary);
	vertexData[1].setUV(0.0f, 1.0f);


	vertexData[2].setPosition(xbinary, ybinary);
	vertexData[2].setUV(0.0f, 0.0f);


	//SecondTriangle
	vertexData[3].setPosition(xbinary, ybinary);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(xbinary + widthbinary, ybinary);
	vertexData[4].setUV(1.0f, 0.0f);


	vertexData[5].setPosition(xbinary + widthbinary, ybinary + heightbinary);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 255, 255);
	}


	/*vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);
	*/


	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
