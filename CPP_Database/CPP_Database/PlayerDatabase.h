#pragma once
#include "Game.h"
#include "Leaderboard.h"
#include <string>

class PlayerDatabase :
	public Game
{
public:


protected:
	//Game Override
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual bool IsGameRunning() override;


	virtual void Update() override;
	virtual void Draw() override;

private:
	bool isGameRunning = true;

	Leaderboard leaderboard;

	void displayMenu();
	std::string getMenuOption();
};

