#pragma once
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace MyGameEngine
{


	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();


		void init(int screenWidth, int screenHeight);
		void update();

		//setters
		void setPosition(const glm::vec2 &newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = newScale;  _needsMatrixUpdate = true;}
		//getters
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		int _screenWidth, _screenHeight;
		glm::mat4 _orthoMatrix;

	};
}