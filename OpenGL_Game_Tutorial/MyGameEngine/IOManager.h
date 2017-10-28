#pragma once
#include <vector>
namespace MyGameEngine
{
	static class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}