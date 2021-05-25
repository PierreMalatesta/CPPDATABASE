#pragma once
#include "Player.h"
#include <string>

class Leaderboard
{
public:

	const int MaxLeaderboardSize = 1000;

	///maxPlayers range between 1 and 100
	///Defined the max capacity of the leaderboard
	Leaderboard(unsigned int maxPlayers = 10);
	~Leaderboard();

	bool IsEmpty() const { return (playersInUse == 0); }
	bool IsFull() const { return (playersInUse >= maxPlayers); }

	unsigned int PlayersInUse() const { return playersInUse; }
	unsigned int MaxPlayers() const { return maxPlayers; }

	unsigned int size() const { return playersInUse; }
	unsigned int capacity() const { return maxPlayers; }

	Player& GetPlayer(unsigned int pos) const;
	Player& operator[](unsigned int pos) const;

	void Draw();
	void AddPlayer(const std::string& name, unsigned int score);
	void AddPlayer(const Player & player);
	void Clear();
	void SortByHighScore();
	void SortByName();

	//binary search the collection
	//returns true on success and updates pos to reflect position found
	//returns false if not found
	bool BinarySearch(const std::string& name, unsigned int& posFound); 

	////return iterators to basic array
	//const Player* begin()  const { return playerList; }
	//const Player* end()  const  { return playerList + playersInUse; }


	bool Load(const char* filename);
	bool Save(const char* filename);

private:
	Player* playerList = nullptr;

	unsigned int maxPlayers = 0;
	unsigned int playersInUse = 0;
};

