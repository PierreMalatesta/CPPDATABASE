#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "PlayerDatabase.h"
#include "iostreamutils.h"

void PlayerDatabase::Init()
{
	//Load the leaderboard from the file

	try
	{
		leaderboard.Load(Leaderboardfilename);

	}

	catch (std::exception& err)
	{
		std::cout << "Error" << err.what() << std::endl;
	}
}

void PlayerDatabase::Shutdown()
{
	//Save the leaderboard to file
	std::cout << "Do you want to save leaderboard on exit (y/n)?" << std::endl;
	
	cinclear();
	unsigned char c;
	std::cin >> c;

	if (c == 'y' || c == 'Y')
		leaderboard.Save(Leaderboardfilename);

}

bool PlayerDatabase::IsGameRunning()
{
	return isGameRunning;
}

void PlayerDatabase::Update()
{
	displayMenu();
	std::string menuOption = getMenuOption();

	if (menuOption == "a")
	{
		addnewPlayer();
	}

	else if (menuOption == "m")
	{
		modifyPlayerByName();
	}

	else if (menuOption == "n")
	{
		leaderboard.SortByName();
	}


	else if (menuOption == "l")
	{
		if (!leaderboard.Load(Leaderboardfilename))
		{
			std::cerr << "Error loading file" << Leaderboardfilename << std::endl;
			cinclear(); 
			int ch = getchar();
		}

		else
		{
			leaderboard.SortByHighScore(); 
		}
	}


	else if (menuOption == "s")
	{
		if (!leaderboard.Save(Leaderboardfilename))
		{
			std::cerr << "Error saving file" << Leaderboardfilename << std::endl;
			cinclear();
			int ch = getchar();
		}
	}


	else if (menuOption == "h")
	{
		hackTheLeaderboardFile();
	}

	else if (menuOption == "s")
	{
		if (!leaderboard.Save(Leaderboardfilename))
		{
			std::cerr << "Error saving file:" << Leaderboardfilename << std::endl;
			cinclear();
			int ch = getchar();
		}
	}

	else if (menuOption == "c")

	{
		leaderboard.Clear();
	}

	else if (menuOption == "q")
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
	std::cout << std::endl << "----Menu----" << std::endl;
	std::cout << "A)dd player" << std::endl;
	std::cout << "M)odify player" << std::endl;
	std::cout << "Sort by N)ame" << std::endl;
	std::cout << "S)ort by highscore" << std::endl;
	std::cout << "C)lear leaderboard" << std::endl;
	std::cout << "L)oad filedata" << std::endl;
	std::cout << "S)ave filedata" << std::endl;
	std::cout << "H)ack filedata" << std::endl;
	std::cout << "Q)uit" << std::endl;
	std::cout << "------------" << std::endl;
	std::cout << "> ";

}

std::string PlayerDatabase::getMenuOption()
{
	std::string userInput;
	cinclear();	//Clear pending input & error flags
	std::cin >> userInput;

	std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
	return userInput;
}

void PlayerDatabase::addnewPlayer()
{
	if (!leaderboard.IsFull())
	{
		Player p;
		if (p.LoadFromConsole())
		{
			leaderboard.AddPlayer(p);
		}
	}

	else
	{
		std::cout << "Leaderboard is full" << std::endl;
		getchar(); 
	}
}

void PlayerDatabase::modifyPlayerByIndex()
{
	cinclear();
	std::cout << "Enter player position to modify> ";
	unsigned int pos; 
	std::cin >> pos;

	if (pos < leaderboard.PlayersInUse())
	{
		leaderboard.GetPlayer(pos).LoadFromConsole();
	}
}

void PlayerDatabase::modifyPlayerByName()
{
	cinclear();
	std::cout << "Enter name of player to modify> ";
	std::string name;
	std::cin >> name;

	//ask the leaderboard to do a bianry search for the player
	//and return the players position in the array
	
	unsigned int pos = 0;

	if (leaderboard.BinarySearch(name, pos))
	{
		//Update the player data
		leaderboard[pos].LoadFromConsole();

		//sort players by highscore
		leaderboard.SortByHighScore();
	}
}

void PlayerDatabase::hackTheLeaderboardFile()
{
	cinclear();

	std::cout << "Enter name of player to modify> ";
	std::string name;
	std::cin >> name;

	cinclear();

	std::fstream f(Leaderboardfilename, std::ios_base::in | std::ios_base::out | std::ios_base::binary); 
	if (f.good())
	{
		//Seek pass the header info (e.g. maxPlayers, playersInUse)
	/*	unsigned int maxPlayers, playersInUse;
		f.read((char*)&maxPlayers, sizeof(maxPlayers));
		f.read((char*)&playersInUse, sizeof(playersInUse));*/
		f.seekg(sizeof(unsigned int) * 2);

		//We can read players one at a time and test their name
		Player p;
		while (!f.eof())
		{
			f.read((char*)&p, sizeof(Player));
			if (name == p.GetName())
			{
				std::cout << "Found player" << name << std::endl;
				
				//Read new player data from console
				p.LoadFromConsole();


				//Move (seek) the cursor back to the start of this player in the file 
				constexpr int sizeOfPlayer = sizeof(Player);
				f.seekg(-sizeOfPlayer, f.cur);
				
				//Overwrite the file data with the new player data
				f.write((const char*)&p, sizeof(Player));

				f.close();


				int ch = getchar();
				return;
			}
		}

		std::cout << "Did not found player:" << name << std::endl;
		f.close();
	}
	else
	{
		std::cerr << "Failed to load file: " << Leaderboardfilename << std::endl;
	}

	int ch = getchar();
}

//void PlayerDatabase::sortLeaderboardByScore()
//{
//	std::sort(leaderboard.begin(), leaderboard.end()); 
//}
