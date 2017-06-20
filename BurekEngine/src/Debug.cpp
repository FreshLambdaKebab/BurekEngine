#include "Debug.h"

#include <iostream>
#include <SDL\SDL.h>

void FatalError(const std::string& error)
{
	std::cout << error << std::endl;
	std::cout << "Press any key to continue..\n";
	int temp;
	std::cin >> temp;
	SDL_Quit();
	exit(420);
}