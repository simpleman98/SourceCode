#pragma once

#include <vector>
#include <GL\glew.h>
#include <SDL\SDL.h>	

#include <MyGameEngine\MyGameEngine.h>
#include <MyGameEngine\Sprite.h>
#include <MyGameEngine\GLSLProgram.h>
#include <MyGameEngine\GLTexture.h>
#include <MyGameEngine\Window.h>
#include <MyGameEngine\Camera2D.h>
#include <MyGameEngine\SpriteBatch.h>
enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();


private:

	void initSystems();

	void processInput();
	void gameLoop();
	void drawGame();
	void initShaders();
	void calculateFPS();

	int _screenWidth;
	int _screenHeight;

	GameState _gameState;
	MyGameEngine::Sprite _sprite;
	

	MyGameEngine::Window _window;
	MyGameEngine::Camera2D _camera;
	MyGameEngine::GLSLProgram _colorProgram;

	MyGameEngine::SpriteBatch _spriteBatch;



	float _fps;
	float _frameTime;
	float _time; 
	float _maxFPS;

};

