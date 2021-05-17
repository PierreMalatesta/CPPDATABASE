#pragma once
#include "Player.h"

class Leaderboard
{
public:

	///maxPlayers range between 1 and 100
	///Defined the max capacity of the leaderboard
	Leaderboard(unsigned int maxPlayers = 10);
	~Leaderboard();

	void Draw();

private:
	Player* playerList = nullptr;

	unsigned int maxPlayers = 0;
	unsigned int playersInUse = 0;
};

