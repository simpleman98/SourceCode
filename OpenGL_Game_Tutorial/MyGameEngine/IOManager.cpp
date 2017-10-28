#include "IOManager.h"
#include <fstream>
namespace MyGameEngine
{
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer)
	{
		std::ifstream file(filePath, std::ios::binary);  // Riding in binary files

		if (file.fail())
		{
			perror(filePath.c_str());
			return false;

		}
		// seek to the end 
		file.seekg(0, std::ios::end);

		//get the file size 
		int fileSize = file.tellg();

		// get the position of the input stream
		file.seekg(0, std::ios::beg);

		// refuce the file size by any header bytes that might be preset 
		//fileSize -= file.tellg();
		// rezises the container so that it contains "fileSize" elements
		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}
}