#pragma once
#include "Leaderboard.h"


class Game
{
public:
	//Default Constructor
	Game();

	//Run the main game loop
	void Run();

protected:

	//Pure virtual functions make this class 'abstruct' so we cannot instantiate it.
	//We must instantiate a derived class which implements these functions
	virtual void Init() = 0;
	virtual void Shutdown() = 0;
	virtual bool IsGameRunning() = 0;

	virtual void Update() = 0;
	virtual void Draw() = 0;

private:
	Leaderboard leaderboard; 
};

