#pragma once
#include <vector>
static class IOManager
{
	public:
		static bool readFileToBuffer(std::string filePath,std::vector<unsigned char>& buffer);
};

