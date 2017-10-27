#include "MainGame.h"

#include <iostream>
#include <string>
#include "Errors.h"

#include "ImageLoader.h"

MainGame::MainGame()
	:_screenWidth(1000),
	_screenHeight(600),
	_time(0.0f),_window(nullptr),
	_gameState(GameState::PLAY)
{

	
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
	
	_sprite.init(-1.0f,-1.0f,2.0f,2.0f);
	_playerTexture = ImageLoader::loadPNG("Textures/sphere.png");


	gameLoop();

}

void MainGame::initSystems()
{
	//Initianal SDL
	SDL_Init(SDL_INIT_EVERYTHING);


	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	// craete Window 
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		fatalProgramError("SDL Window could not be created!");
	}
	
	// create Context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalProgramError("SDL_GL context could not be created!");

	}

	// init glew 
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalProgramError("Could not initialize glew!");
	}
	
	// Set background Color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 


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
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;

		}
	}
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();

		_time += 0.001f;
		drawGame();
	}
}

void MainGame::drawGame()
{
	
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  
	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation,0);

	/*GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);*/
	_sprite.draw();   

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);

}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();

}



