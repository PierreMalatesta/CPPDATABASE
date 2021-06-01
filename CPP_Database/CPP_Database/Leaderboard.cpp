#include "Leaderboard.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Leaderboard::Leaderboard(unsigned int _maxPlayers)
	:maxPlayers(_maxPlayers), playersInUse(0)
{
	if (maxPlayers == 0)
		maxPlayers = 10;

	if(maxPlayers > 100)
		maxPlayers = 100;

	playerList = new Player[maxPlayers];
}

Leaderboard::~Leaderboard()
{
	delete[] playerList;
}

Player& Leaderboard::GetPlayer(unsigned int pos) const
{
	if (pos > playersInUse)
	{
		throw std::out_of_range("out of bounds.");
	}
	return playerList[pos];

	 return playerList[pos]; 
}

Player& Leaderboard::operator[](unsigned int pos) const
{
	return GetPlayer(pos);
}

void Leaderboard::Draw()
{
	std::cout << "======================" << std::endl;
	std::cout << "== Leaderboard	  ==" << std::endl;
	std::cout << "======================" << std::endl;

	if (!IsEmpty())
	{
		for (unsigned int i = 0; i < playersInUse; i++)
		{
			std::cout << " [" << i << "] "; 
			playerList[i].Draw();
		}
	}

	else
	{
		std::cout << "...Empty..." << std::endl;
	}
}

void Leaderboard::AddPlayer(const std::string& name, unsigned int score)
{
	AddPlayer(Player(name.c_str(), score));
}

void Leaderboard::AddPlayer(const Player& player)
{
	if (playersInUse < maxPlayers)
	{
		playerList[playersInUse] = player;
		playersInUse++;
	}

	else
	{
		throw std::out_of_range("out of bounds. Leaderboard full.");
	}
}

void Leaderboard::Clear()
{
	playersInUse = 0;
}

bool comparePlayerScore(const Player& lhs, const Player& rhs)
{
	return lhs.GetHighScore() > rhs.GetHighScore();
}

void Leaderboard::SortByHighScore()
{
	std::sort(playerList, playerList + playersInUse, comparePlayerScore); 
}


bool comparePlayerNames(const Player& lhs, const Player& rhs)
{
	return (strcmp (lhs.GetName(), rhs.GetName()) < 0);
}

void Leaderboard::SortByName()
{
	std::sort(playerList, playerList + playersInUse, comparePlayerNames);

}
bool Leaderboard::BinarySearch(const std::string& name, unsigned int& posFound)
{
	//Sort array by highscore
	const int arraySize = 10;

	//int array[arraySize] = {};

	int start_index = 0; 
	int end_index = playersInUse - 1; 

	while (start_index <= end_index)
	{
		int pivot = (start_index + end_index) / 2;

		if (playerList[pivot].GetName() == name)
		{
			posFound = pivot;
			return true;
		}

		if (name < playerList[pivot].GetName())
			end_index = pivot - 1;
		else
			start_index = pivot + 1;
	}

	//implement binary algortithm based on alphabetical order
	

	//set position and return true if found
	return false;
}
int binarySearch(int array[], int start_index, int end_index, int key)
{
	return 1;
}


bool Leaderboard::Load(const char* filename)
{
	std::fstream file;
	file.open(filename, std::ios_base::in | std::ios_base::binary);
	if (file.is_open())
	{
		//<-- load playersInUse

		int index = 0;
		//Set playerList to be array of size playersInUse
		file.read((char*)&playersInUse, sizeof(int));

		playerList = new Player[maxPlayers];

		for (int i = 0; i < playersInUse; i++) //read lines until run out of lines
		{
			file.read((char*)&playerList[i], sizeof(Player));
		}
		file.close();

		return true;
	}
	return false;
}

bool Leaderboard::Save(const char* filename)
{
		std::fstream file;
		file.open(filename, std::ios_base::out | std::ios_base::binary);

		if (file.is_open())
		{
			//save how many players are in the list
			file.write((char*)&playersInUse, sizeof(unsigned int));

			for (int i = 0; i < playersInUse; ++i)
			{
				//save player details (name and highscore) individually
				file.write((char*)&playerList[i], sizeof(Player));
			}
		}
		else
		{
			return false;
		}
		file.close();
		return true;
}


