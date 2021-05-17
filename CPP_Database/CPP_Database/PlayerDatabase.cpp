#include "PlayerDatabase.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>


void PlayerDatabase::Init()
{
	//Load the leaderboard from the file

}

void PlayerDatabase::Shutdown()
{
	//Save the leaderboard to file

}

bool PlayerDatabase::IsGameRunning()
{
	return isGameRunning;
}

void PlayerDatabase::Update()
{
	std::string menuOption = getMenuOption();

	if (menuOption == "n")
	{
		std::cout << "New Player" << std::endl;
	}
	else if (menuOption == "n")
	{
		isGameRunning = false;
	}
}

void PlayerDatabase::Draw()
{
	system("cls");
	leaderboard.Draw();
}


void PlayerDatabase::displayMenu()
{
}

std::string PlayerDatabase::getMenuOption()
{
	std::cout << "====Menu====" << std::endl;
	std::cout << "Q)uit" << std::endl;

	std::string userInput;
	std::cin.ignore(std::cin.rdbuf()->in_avail());	//Clear pending input
	std::cin >> userInput;

	std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
	return userInput;
}
