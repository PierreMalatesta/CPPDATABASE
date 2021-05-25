#include "iostreamutils.h"
#include <iostream>

void cinclear()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());	//Clear pending input
}