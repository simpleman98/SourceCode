#include "Errors.h"
#include <iostream>
#include <cstdlib>

#include <SDL\SDL.h>
namespace MyGameEngine
{
	void fatalProgramError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit !";
		int tmp;
		std::cin >> tmp;
		exit(69);

	}
}