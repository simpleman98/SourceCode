#pragma once

#include <GL\glew.h>
#include <SDL\SDL.h>	
#include <iostream>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();


private:
	SDL_Window* _window;
	void initSystems();

	void processInput();
	void gameLoop();
	void drawGame();
	void initShaders();


	int _screenWidth;
	int _screenHeight;

	GameState _gameState;
	Sprite _sprite;
	std::vector<Sprite*> _sprites;



	GLSLProgram _colorProgram;

	float _time; 

};

