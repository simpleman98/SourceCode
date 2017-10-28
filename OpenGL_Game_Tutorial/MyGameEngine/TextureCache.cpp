#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
namespace MyGameEngine
{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		// scan for texture maps

		// The keyword auto is similar to var in C#
		//std::map<std::string,GLTexture>::iterator mit = _textureMap.find(texturePath);

		//lookup the texture and see if its in the map
		auto mit = _textureMap.find(texturePath);

		//check if its not in the map
		if (mit == _textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			/*	std::pair<std::string, GLTexture> newPair(texturePath, newTexture);
				_textureMap.insert(newPair); */

				//std::pair<std::string, GLTexture> newPair(texturePath, newTexture);

				//Insert it into the map
			_textureMap.insert(make_pair(texturePath, newTexture));
			std::cout << "Loaded Texture! \n";

			return newTexture;
		}

		std::cout << "Used Cached Texture! \n";
		return mit->second;
	}
}