#pragma once
#include "GLTexture.h"
#include <string>
namespace MyGameEngine
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}