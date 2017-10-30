#include "MainGame.h"

#include <iostream>
#include <string>

#include <MyGameEngine\Errors.h>



MainGame::MainGame()
	:_screenWidth(1200),
	_screenHeight(700),
	_time(0.0f), 
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	_camera.init(_screenWidth,_screenHeight);
	
}

MainGame::~MainGame()
{

}


void MainGame::Run()
{
	initSystems();
   /* Sprite s(_screenWidth, _screenHeight);
	_sprite = s;
	_sprite.initNormalized(0.0f, 0.0f, 500.0f, 500.0f);*/
	_sprites.push_back(new MyGameEngine::Sprite());
	_sprites.back()->init(0.0f, 0.0f,(float) (200), (float)(200), "Textures/sphere.png");

	/*_sprites.push_back(new MyGameEngine::Sprite());
	_sprites.back()->init((float)_screenWidth / 2,0.0f, (float)_screenWidth / 2, (float)_screenHeight / 2, "Textures/sphere.png");*/


	


	//_playerTexture = ImageLoader::loadPNG("Textures/sphere.png");


	gameLoop();

}

void MainGame::initSystems()
{
	//Initianal SDL
	MyGameEngine::init();

	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	// Initialize Shaders
	initShaders();

}

void MainGame::processInput()
{
	SDL_Event evnt;

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
					_camera.setPosition(_camera.getPosition()+ glm::vec2(0.0, 1.0));
					break;
				case SDLK_s:
					_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -1.0));
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
		_time += 0.1f;

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

	glUniformMatrix2fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
 
	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}

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



