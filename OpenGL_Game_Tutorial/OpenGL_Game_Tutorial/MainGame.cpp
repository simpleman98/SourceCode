#include "MainGame.h"

#include <iostream>
#include <string>

#include <MyGameEngine\Errors.h>
#include <MyGameEngine\ResourceManager.h>
#include <vector>



MainGame::MainGame()
	:_screenWidth(1200),
	_screenHeight(700),
	_time(0.0f), 
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);

	

	
	
}

MainGame::~MainGame()
{

}


void MainGame::Run()
{
	
	initSystems();



	gameLoop();

}

void MainGame::initSystems()
{
	//Initianal SDL
	MyGameEngine::init();

	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	// Initialize Shaders
	initShaders();
	//_spriteBatch.init();

	MyGameEngine::Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	_graph.init(_screenWidth, _screenHeight, color);

}

void MainGame::processInput()
{
	SDL_Event evnt;
	const float CAMERA_SPEED = 20;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{
				case SDLK_w:
					_camera.setPosition(_camera.getPosition()+ glm::vec2(0.0, CAMERA_SPEED));
					break;
				case SDLK_s:
					_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
					break;
				case SDLK_a:
					_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0));
					break;
				case SDLK_d:
					_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0));
					break;

				case SDLK_q:
					_camera.setScale(_camera.getScale() + SCALE_SPEED);
					break;

				case SDLK_e:
					_camera.setScale(_camera.getScale() - SCALE_SPEED);
					break;

			}

		}
	}
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		//used for frame time measuring
		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.01;

		_camera.update();

		drawGame();

		calculateFPS();
		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f /_maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}


	}
}

void MainGame::drawGame()
{
	
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  
	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);


	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation,0);

	//GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);


	//set the camera matrix 
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
 
	
	_graph.startDraw();

	_graph.drawAxes(1);
	_graph.drawCircel();
	_graph.endDraw();

	//_graph.drawAxis();

	//_graph.drawGrid();
	//_graph.drawGraph();



	


	//_spriteBatch.begin();





	//MyGameEngine::Color white;
	//white.r = 255;
	//white.g = 255;
	//white.b = 255;
	//white.a = 255;

	//MyGameEngine::Color black;
	//black.r = 0;
	//black.g = 0;
	//black.b = 0;
	//black.a = 255;




	////_spriteBatch.draw(pos, uv, (GLuint)0, 1, white);
	////_spriteBatch.draw(pos, uv, (GLuint)0, 1, black);

	//static float positionX = 0.0f;
	//static float positionY = 0.0f;

	//float RectWidth = 5.0f;
	//float RectHeight = 5.0f;

	//glm::vec4 uv(0.0f, 0.0f, 0.0f, 0.0f);

	//static int presign = 1;

	//if (AreSecondsElapsed(0.0f))
	//{
	//	_spritePositions.push_back(glm::vec4(positionX, positionY, RectWidth, RectHeight));
	//	positionY += (2.5 * presign);

	//	if (positionY > (_screenHeight /2)- RectHeight)
	//	{
	//		presign = -1;
	//		positionX+= 10;
	//	}

	//	if (positionY < 0.0f)
	//	{
	//		presign = 1;
	//		positionY += (2.5);
	//		positionX += 10;
	//	}
	//	
	//}



	//

	//for (int i = 0; i < _spritePositions.size(); i++)
	//{
	//	_spriteBatch.draw(_spritePositions[i], uv, (GLuint)0, 1, white);
	//}
	//
	//for (int i = -_screenWidth; i <= _screenWidth; i++)
	//{
	//	_spriteBatch.draw(glm::vec4(i,0,1,1), uv, (GLuint)0, 1, white);
	//}
	
	

	

	//static MyGameEngine::GLTexture texture = MyGameEngine::ResourceManager::getTexture("Textures/sphere.png");

	//

	//for (int i = 0; i < 1000; i++)
	//{
	//	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	//	_spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
	//}

	//_spriteBatch.end();
	//_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	_window.swapBuffer();

}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();

}

void MainGame::calculateFPS()
{
	static const int NUM_SAMPLES = 10; // number of average
	static float frameTime[NUM_SAMPLES];
	static int currentFrame = 0;


	static float prevTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;

	frameTime[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTime[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 60.0f;
	}
	
}

bool MainGame::AreSecondsElapsed(float seconds)
{
	Uint32 deltaTime = 0;
	static Uint32 oldTime = 0;
	Uint32 actualTime = SDL_GetTicks();

	deltaTime = SDL_GetTicks() - oldTime;
	if (deltaTime >= (int)(seconds * 1000))
	{
		oldTime = actualTime;
		return true;
	}
	
	return false;

}




