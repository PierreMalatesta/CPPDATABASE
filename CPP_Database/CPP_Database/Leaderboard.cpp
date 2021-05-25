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

bool Leaderboard::Load(const char* filename)
{

	std::ifstream fin( filename, std::ios_base::in | std::ios_base::binary);
	if (fin.good())
	{
		//Read the max players, reallocate the playerlist to hold this many players
		unsigned int maxPlayers;
			fin.read((char*)&maxPlayers, sizeof(unsigned int));

			if (maxPlayers > MaxLeaderboardSize)
			{
				std::cerr << "Leaderboard:: Invalid file format. maxPlayers is too large" << std::endl;
				fin.close();
				return false;
				//throw std::exception("Invalid file data");
			}

			//Reallocate our playerList if its a different size to that from the file
			if (this->maxPlayers != maxPlayers)
			{
				this->maxPlayers = maxPlayers; 
				delete[] this->playerList; 
				this->playerList = new Player[maxPlayers];
			}

		//Read the players in use

			unsigned int playersInUse;
			fin.read((char*)&playersInUse, sizeof(unsigned int));

			if (playersInUse > maxPlayers)
			{
				std::cerr << "Leaderboard:: Invalid file format. playersInUse is too large" << std::endl;
				fin.close();
				return false;
				//throw std::exception("Invalid file data");
			}

			this->playersInUse = playersInUse;

		//Read the array of players (up to players in use)
			fin.read((char*)playerList, (std::streamsize)(playersInUse * sizeof(Player)));

		fin.close();
		return true;
	}

	return false;
}

bool Leaderboard::Save(const char* filename)
{
	std::ofstream fout(filename, std::ios_base::out | std::ios_base::binary);

	if (fout.good())
	{
		//write out maxplayers to file 
		fout.write((const char*)&maxPlayers, sizeof(maxPlayers));

		//write out playersInUse to file 
		fout.write((const char*)&playersInUse, sizeof(playersInUse));


		//write out the playerList[playersInUse]
		fout.write((const char*)&playerList, (std::streamsize)playersInUse * sizeof(Player));


		fout.close();
		return true;
	}


	return false;
}


//bool Leaderboard::Search(const std::string& name, unsigned int& posFound)
//{
//	//Need to sort collection before doing a binary search 
//	SortByName();
//
//	unsigned int l = 0;
//	unsigned int r = playersInUse - 1;
//	unsigned int m;
//
//	while (l <= r)
//	{
//		m = (l + r) / 2;
//
//		if (name == playerList[m].GetName())
//		{
//			posFound = m;
//			return true;
//		}
//
//		else if (name < playerList[m].GetName())
//		{
//			r = m - 1;
//		}
//
//		else if (name > playerList[m].GetName())
//		{
//			l = m + 1;
//		}
//	}
//
//	return false;
//}


